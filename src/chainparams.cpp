// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include "base58.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe5;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xd8;
        vAlertPubKey = ParseHex("048adb32249d8e8ac6b9bd25992033479c13e8a9c50b8e8d8b6abdc17ff711d35e9619143e711305ea9cf82bb619e2766bd2841b7f751c43089115737efc82caa1");
        nDefaultPort = 22937;
        nRPCPort = 22938;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block.
            // transaction:  Coinbase(hash=3c8eb5ab2277426f2f48bd70eeb32416b1c94456a3e56e1871d15b568dde3e1e, nTime=1525989555, ver=1, vin.size=1, vout.size=1, nLockTime=0)
            // CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a284f63742032322c20323031373a20426974636f696e2070726963652061626f76652024362c303030)
            // CTxOut(empty)

        const char* pszTimestamp = "ARENON - The Gaming Currency No.1 - Masternode - FuSSeL - DPR - qounsX - Glenviddich";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1525989555, vin, vout, 0);

        LogPrintf("Genesis mainnet Transaction:  %s\n", txNew.ToString().c_str());

        genesis.vtx.push_back(txNew);

        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1525989555;
		genesis.nBits = 520167231; // bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 142539;

        hashGenesisBlock = genesis.GetHash();

        printf("%s\n", genesis.GetHash().ToString().c_str());
        printf("%s\n", genesis.BuildMerkleTree().ToString().c_str());

        assert(hashGenesisBlock == uint256("0x5f25305cfc665f2ae8b3fc758c83caff78e49ad23cfe36d4540f6de2da3d637f"));
        assert(genesis.hashMerkleRoot == uint256("0xddb01c168dc5e46f23a3bca9bc295b4384354ab55b0f713cdf20586113fbabc9"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,23);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,43);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("0",  "85.214.211.186")); //185.114.226.103
        vSeeds.push_back(CDNSSeedData("1",  "185.114.226.103"));


        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        //vFixedSeeds.clear();
        //vSeeds.clear();

        //getHardcodedSeeds(vFixedSeeds);

        nPoolMaxTransactions = 3;
        strSporkKey = "04c55d693024e18327b1d25ee44f8b7a561deac17805f50eee68acbc7b540d1e32fbf52f64a27838cb6f4384ddcfa3c3d8c44b0d268ee33e59ae919f218c537ee3";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "AVjui6eyjMHU37MLKr4qb49jURXr2f3ApK";


        nLastPOWBlock = 100;
        nPOSStartBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 231;
        pchMessageStart[1] = 96;
        pchMessageStart[2] = 51;
        pchMessageStart[3] = 129;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04d8a7e2ad27f7da4bf7821d2138a3619606c21404b9fc48b8b1c4753c7a7373c7971f6549987444dd84c7a2345e3158ff0af0b2e787d7cd7b1af3e74864982d5f");
        nDefaultPort = 27170;
        nRPCPort = 27171;
        strDataDir = "testnet";

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x5f25305cfc665f2ae8b3fc758c83caff78e49ad23cfe36d4540f6de2da3d637f"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,73);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,83);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
