#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>

#include "Enclave.h"
#include "NetworkManagerServer.h"
#include "Messages.pb.h"
#include "UtilityFunctions.h"
#include "remote_attestation_result.h"
#include "LogBase.h"
#include "../GeneralSettings.h"

using namespace std;
using namespace util;

class MessageHandler {

public:
    MessageHandler(int port);
    virtual ~MessageHandler();

    sgx_ra_msg3_t* getMSG3();
    int init();
    void start();
    vector<string> incomingHandler(string v, int type);

private:
    sgx_status_t initEnclave();
    uint32_t getExtendedEPID_GID();
    sgx_status_t getEnclaveStatus();

    void assembleAttestationMSG(Messages::AttestationMessage msg, ra_samp_response_header_t **pp_att_msg);
    string handleAttestationResult(Messages::AttestationMessage msg);
    void assembleMSG2(Messages::MessageMSG2 msg, sgx_ra_msg2_t **pp_msg2);
    string handleMSG2(Messages::MessageMSG2 msg);
    string handleMSG0(Messages::MessageMsg0 msg);
    string generateMSG1();
    string handleVerification();
    string generateMSG0();
    string createInitMsg(int type, string msg);

protected:
    virtual string verificationSuccessful() = 0;
    virtual string handleMeasurementListResult(Messages::SecretMessage ml_msg) {}
    virtual string handleApplicationNonce(Messages::SecretMessage msg) {}
    virtual string handleAppHMACResult(Messages::SecretMessage sec_msg) {}

protected:
    Enclave *enclave = NULL;
    NetworkManagerServer *nm = NULL;

private:
    int busy_retry_time = 4;
};

#endif











