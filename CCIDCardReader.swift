//
//  BuiltInPIVCardReader.swift
//  Smart Card Utility iOS
//
//  Created by timothy perfitt on 8/7/22.
//  Copyright © 2022 Twocanoes Software. All rights reserved.
//

import Foundation
import CryptoTokenKit

enum CardState {
    case NotInserted
    case Inserted
    case Connected  //connected to applet

}

enum SmartCardError:Error{

    case invalidSignature(_ msg:String="invalidSignature",certData:Data=Data())
    case APDUSecurityError
    case APDUInvalidDataError
//    case APDUNotFoundError(pivObject:PIVObject?=nil)
    case APDUAuthenticationBlockedError
    case APDUCommunicationError
    case APDUTransactionError(UInt8)
    case APDUOtherError(UInt8,UInt8)

}

class CCIDCardReader: NSObject {
    var tkSmartCard:TKSmartCard
    let semaphore = DispatchSemaphore(value: 0)
    init(tkSmartCard: TKSmartCard) {
        self.tkSmartCard = tkSmartCard
    }

    // Build a short APDU: [CLA][INS][P1][P2][Lc?][Data?][Le?]
    private func buildAPDU(cla: UInt8, ins: UInt8, p1: UInt8, p2: UInt8, lcByteLength: UInt8, data: Data?, le: UInt16?, leByteLength: UInt8) -> Data {
        var apdu = Data([cla, ins, p1, p2])

        if let data = data, data.count > 0 {
            // short length only (Lc fits into 1 byte)
            apdu.append(UInt8(data.count & 0xFF))
            apdu.append(data)
        }

        if let le = le {
            // short Le (1 byte) if requested
            if leByteLength == 1 {
                apdu.append(UInt8(le & 0xFF))
            } else {
                // If extended length were needed, we’d need 0x00 + two-byte Le.
                // This codebase only uses short APDUs; keep it simple.
                apdu.append(UInt8(le & 0xFF))
            }
        }

        return apdu
    }

    func sendAPDU(cla:UInt8, ins:UInt8,p1:UInt8,p2:UInt8, lcByteLength:UInt8=1,data:Data?,le:UInt16?=nil, leByteLength:UInt8=1) -> Data? {
        var returnData = Data()

        let apdu = buildAPDU(cla: cla, ins: ins, p1: p1, p2: p2, lcByteLength: lcByteLength, data: data, le: le, leByteLength: leByteLength)

        tkSmartCard.useCommandChaining = true

        tkSmartCard.beginSession { sessionSuccess, err in
            self.semaphore.signal()
        }
        let _ = semaphore.wait(timeout: DispatchTime.now()+10)

        var transceiveResult: (Data?, Error?) = (nil, nil)
        let replySemaphore = DispatchSemaphore(value: 0)

        // Use TKSmartCard transmit API on macOS
        tkSmartCard.transmit(apdu) { response, error in
            transceiveResult = (response, error)
            replySemaphore.signal()
        }

        let _ = replySemaphore.wait(timeout: DispatchTime.now() + 10)

        tkSmartCard.endSession()

        if let error = transceiveResult.1 {
            // Communication error
            _ = error // suppress unused warning
            return nil
        }

        guard let resp = transceiveResult.0 else {
            return nil
        }

        // CryptoTokenKit transmit returns [response data][SW1][SW2]
        returnData.append(resp)

        return returnData
    }

    func disconnectCard() {
        if tkSmartCard.isValid == true {
            endSession()
        }
    }

    func endSession() {
        tkSmartCard.endSession()
    }

}
