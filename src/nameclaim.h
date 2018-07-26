#ifndef BITCOIN_NAMECLAIM_H
#define BITCOIN_NAMECLAIM_H

#include "script/script.h"
#include "uint256.h"
#include "primitives/transaction.h"
#include <vector>
#include "rpcprotocol.h"

// This is the max claim script size in bytes, not including the script pubkey part of the script.
// Scripts exceeding this size are rejected in CheckTransaction in main.cpp
#define MAX_CLAIM_SCRIPT_SIZE 8192

// this is the min number of account_name 
#define MIN_VERIFY_ACCOUNTNAME 10

// This is the max claim name size in bytes, for all claim trie transactions. 
// Scripts exceeding this size are rejected in CheckTransaction in main.cpp
#define MAX_CLAIM_NAME_SIZE 255

CScript ClaimNameScript(std::string name, std::string value);
CScript SupportClaimScript(std::string name, uint160 claimId);
CScript UpdateClaimScript(std::string name, uint160 claimId, std::string value); 

// Parse the script and parse the data in the script.
bool DecodeClaimScript(const CScript& scriptIn, int& op, std::vector<std::vector<unsigned char> >& vvchParams);
bool DecodeClaimScript(const CScript& scriptIn, int& op, std::vector<std::vector<unsigned char> >& vvchParams, CScript::const_iterator& pc);

// Remove the redundant script operations from the script.
CScript StripClaimScriptPrefix(const CScript& scriptIn);
CScript StripClaimScriptPrefix(const CScript& scriptIn, int& op);
uint160 ClaimIdHash(const uint256& txhash, uint32_t nOut);
std::vector<unsigned char> uint32_t_to_vch(uint32_t n);
uint32_t vch_to_uint32_t(std::vector<unsigned char>& vchN);
// get size of the claim script, minus the script pubkey part 
size_t ClaimScriptSize(const CScript& scriptIn);
// get size of the name in a claim script, returns 0 if scriptin is not a claimetrie transaction 
size_t ClaimNameSize(const CScript& scriptIn); 

/*Used as Verify that the account name is valid*/
CScript VerifyClaimScriptPrefix(const CScript& scriptIn,const CTxOut& txout);
CScript VerifyClaimScriptPrefix(const CScript& scriptIn, int& op,const CTxOut& txout);
bool VerifyDecodeClaimScript(const CScript& scriptIn, int& op, std::vector<std::vector<unsigned char> >& vvchParams,const CTxOut& txout);
bool VerifyDecodeClaimScript(const CScript& scriptIn, int& op, std::vector<std::vector<unsigned char> >& vvchParams, CScript::const_iterator& pc,const CTxOut& txout);



#endif // BITCOIN_NAMECLAIM_H
