// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2017 The Dash developers
// Copyright (c) 2017-2018 SECI developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "base58.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"
#include "arith_uint256.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);

    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "WSJ 28/Mar/2018: Many Asia Markets Rebound From Losses";
    const CScript genesisOutputScript = CScript() << ParseHex("04b36e3c4a54589d96c47dbdec6672477b6c4a01434a5f42257976d9053bcf8f809b857900ac246162b60c13ac25351952bea1e128d60a4e110ec9390fd51dfe95");
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

const arith_uint256 maxUint = UintToArith256(uint256S("ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";

        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("00000d2e96a48dbbc13255fcfa039a61cf8511567d861543010c0bab630e0018");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 30 * 60; //30 minutes
        consensus.nPowTargetSpacing = 60; //1 minute

        consensus.fPowD106SwitchHeight = consensus.DifficultyAdjustmentInterval();

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = false;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 9576; 
        consensus.nMinerConfirmationWindow = 10080;  

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1523016742; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("000000000000000000000000000000000000000000000000000000eee8866296");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        // Masternode payments are enforced 3 days after the Instamine protection ends at 10800 blocks

        consensus.MasternodePaymentStartHeight = 16560;

         /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xb0;
        pchMessageStart[1] = 0xd2;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xc3;
        nDefaultPort = 9819;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1523016742, 1721742, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();
		
		/*
		Mainnet ---
		nonce: 1721742
		time: 1523016742
		hash: 00000d2e96a48dbbc13255fcfa039a61cf8511567d861543010c0bab630e0018
		merklehash: 66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4
		*/
	
        assert(consensus.hashGenesisBlock == uint256S("00000d2e96a48dbbc13255fcfa039a61cf8511567d861543010c0bab630e0018"));
        assert(genesis.hashMerkleRoot == uint256S("66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4"));

        vSeeds.push_back(CDNSSeedData("dnsseed.seci.io", "dnsseed.seci.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("00000d2e96a48dbbc13255fcfa039a61cf8511567d861543010c0bab630e0018")},
                {     225, uint256S("000000007977232644949f5cf4bbc08d1ff7194a3e81fb8dd6bef06041313eb8")},
            }
        };

        // treasury payment addresses 
        vTreasuryRewardAddress = {
            "3FMmX2S8yknSZ4NsxtxbQwQkgvbe81R5kR"
        };

        // [1] UNIX timestamp of last known number of transactions
        // [2] total number of transactions between genesis and that timestamp
        //     (the tx=... number in the SetBestChain debug.log lines)
        // [3] estimated number of transactions per second after that timestamp
        chainTxData = ChainTxData{
            1523036278,
            245,
            1
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";

        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("00000dbd0851f08eb802e0e822c9475512c04b402f9040b0d7b6bfd1b1356033");
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.BIP102HeightDelta = 0;

        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 1 * 60; //1 minutes
        consensus.nPowTargetSpacing = 10; //seconds 

        consensus.fPowD106SwitchHeight = 30;

        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;

        consensus.nRuleChangeActivationThreshold = 6480; 
        consensus.nMinerConfirmationWindow = 8640; //1 day

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1523016742; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 14400;

        pchMessageStart[0] = 0x2a;
        pchMessageStart[1] = 0x1e;
        pchMessageStart[2] = 0xd5;
        pchMessageStart[3] = 0xc3;
        nDefaultPort = 9829;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1523003790, 3039562, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();

		/*
		Testnet ---
		nonce: 3039562
		time: 1523003790
		hash: 00000dbd0851f08eb802e0e822c9475512c04b402f9040b0d7b6bfd1b1356033
		merklehash: 66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4
		*/
		
		assert(consensus.hashGenesisBlock == uint256S("00000dbd0851f08eb802e0e822c9475512c04b402f9040b0d7b6bfd1b1356033"));
        assert(genesis.hashMerkleRoot == uint256S("66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4"));

        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("dnsseed.seci.io", "dnsseed.seci.io"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;

        checkpointData = (CCheckpointData) {
            {
                {     0, uint256S("00000dbd0851f08eb802e0e822c9475512c04b402f9040b0d7b6bfd1b1356033")},
            }
        };

        vTreasuryRewardAddress = {
            "93E69rX4oPF88cZKU1kVuw8apasc2txBYF"
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("000007a6ef1ada4c88e5e1194fcdca00496f900bb4a715935a6150027c5e2b34");
        consensus.BIP65Height = 0; 
        consensus.BIP66Height = 0; 
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.BIP102HeightDelta = 0;

        consensus.nPowAveragingWindow = 8;
        assert(maxUint/UintToArith256(consensus.powLimit) >= consensus.nPowAveragingWindow);
        consensus.nPowMaxAdjustDown = 31; // Zawy adjustment: (1 - 1/0.765)x100 (0.765 = v1b)
        consensus.nPowMaxAdjustUp = 23.7; // Zawy adjustment: 1- 1/(1+.31)x100 = 23.7

        consensus.nPowTargetTimespan = 60; //1 minute
        consensus.nPowTargetSpacing = 1; //1 second

        consensus.fPowD106SwitchHeight = 30;

        consensus.fDigishieldDifficultyCalculation = false;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowAllowDigishieldMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;

        consensus.nRuleChangeActivationThreshold = 5400; 
        consensus.nMinerConfirmationWindow = 7200; 

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1523016742;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1514764800;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nOverrideRuleChangeActivationThreshold = 1; 

        // Deployment of SegWit2x
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].bit = 4;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nStartTime = 1523016742; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nTimeout = 1514764800; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideMinerConfirmationWindow = 1; 
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT2X].nOverrideRuleChangeActivationThreshold = 1; 

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0");

        consensus.MasternodePaymentStartHeight = 14400;

        pchMessageStart[0] = 0x6e;
        pchMessageStart[1] = 0x5c;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0x14;
        nDefaultPort = 9839;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1523003789, 988655, 0x1e0ffff0, 1, 10 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();
		
		/*
		REGTEST ---
		nonce: 988655
		time: 1523003789
		hash: 000007a6ef1ada4c88e5e1194fcdca00496f900bb4a715935a6150027c5e2b34
		merklehash: 66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4
		*/

        assert(consensus.hashGenesisBlock == uint256S("000007a6ef1ada4c88e5e1194fcdca00496f900bb4a715935a6150027c5e2b34"));
        assert(genesis.hashMerkleRoot == uint256S("66a0660d69e4ca7bf9f8beb8cbb2b6b18ca6f456895023f3e184487ac00746d4"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("000007a6ef1ada4c88e5e1194fcdca00496f900bb4a715935a6150027c5e2b34") )
        };

        vTreasuryRewardAddress = {
            "2N6TJncxtMLSqEurFaEGtpLxdvq5wiVcR6S"
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0xA2)(0xAE)(0xC9)(0xA6).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x46)(0x00)(0x2A)(0x10).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
        return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
        return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}


std::string CChainParams::GetTreasuryRewardAddressAtHeight(int nHeight) const {
    size_t i = nHeight % vTreasuryRewardAddress.size();
    return vTreasuryRewardAddress[i];
}

CScript CChainParams::GetTreasuryRewardScriptAtHeight(int nHeight) const {
    CseciAddress address(GetTreasuryRewardAddressAtHeight(nHeight).c_str());
    assert(address.IsValid());
    assert(address.IsScript());
    CScriptID scriptID = boost::get<CScriptID>(address.Get()); // Get() returns a boost variant
    CScript script = CScript() << OP_HASH160 << ToByteVector(scriptID) << OP_EQUAL;
    return script; 
}

std::string CChainParams::GetTreasuryRewardAddressAtIndex(int i) const {
    assert(i >= 0 && i < vTreasuryRewardAddress.size());
    return vTreasuryRewardAddress[i];
}


