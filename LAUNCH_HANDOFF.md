# Fizzlewick (FIZZ) Mainnet Launch Handoff

**Date:** 13 October 2026  
**Branch:** `mainnet-launch`  
**Repo:** https://github.com/fivemil/FIZZ  
**Companion pool:** https://github.com/5mil/tpool  

**Goal:** Launch Fizzlewick as a public mainnet test platform today.  
People may do with the coins as they will. This is **not** a monetary product and carries no value claims.

---

## 1. Current Status

| Item | Status |
|------|--------|
| Poetic subsidy (`GetBlockSubsidy`) | Already applied on master |
| Docs (README / LAUNCH / FIZZLEWICK) | Updated on `mainnet-launch` |
| CMainParams changes (magic, port, genesis, prefixes, etc.) | Written on `mainnet-launch` |
| Full `chainparams.cpp` (other networks + factories) | **Incomplete** – needs restore from master |
| Binary rename / client branding | Not done (optional) |
| Public seeds / explorer | Not done (post-launch) |

**Branch URL:** https://github.com/fivemil/FIZZ/tree/mainnet-launch

---

## 2. Required Code Fix (must do before build)

The file `src/kernel/chainparams.cpp` on `mainnet-launch` currently contains only the new `CMainParams` class.  
The rest of the file (TestNet, TestNet4, RegTest, SigNet + factory functions) was truncated during automated edits and **must be restored**.

### Recommended fix (cleanest)

```bash
git fetch origin
git checkout mainnet-launch
git checkout master -- src/kernel/chainparams.cpp   # restore full original file
```

Then re-apply **only** the following changes to the `CMainParams` class and the shared `CreateGenesisBlock` helper:

#### A. Shared genesis timestamp (near top of file)

Replace:
```cpp
const char* pszTimestamp = "The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
```
with:
```cpp
const char* pszTimestamp = "Lo, another ledger of flickering wicks. Mine if you must, but mind the smoke.";
```

#### B. Inside `CMainParams` constructor – replace the whole body with this:

```cpp
CMainParams(const MainNetOptions& opts) {
    m_chain_type = ChainType::MAIN;
    consensus.signet_blocks = false;
    consensus.signet_challenge.clear();
    consensus.nSubsidyHalvingInterval = 210000;

    // Clean start — modern features from height 1
    consensus.BIP34Height = 1;
    consensus.BIP34Hash = uint256{};
    consensus.BIP65Height = 1;
    consensus.BIP66Height = 1;
    consensus.CSVHeight = 1;
    consensus.SegwitHeight = 1;
    consensus.MinBIP9WarningHeight = 0;

    consensus.powLimit = uint256{"00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff"};
    consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
    consensus.nPowTargetSpacing = 10 * 60;
    consensus.fPowAllowMinDifficultyBlocks = true;  // public test platform
    consensus.enforce_BIP94 = false;
    consensus.fPowNoRetargeting = false;

    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = Consensus::BIP9Deployment::NEVER_ACTIVE;
    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].min_activation_height = 0;
    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].threshold = 1815;
    consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].period = 2016;

    ApplyDeploymentOptions(opts.dep_opts);

    consensus.nMinimumChainWork = uint256{};
    consensus.defaultAssumeValid = uint256{};

    // Fizzlewick mainnet magic
    pchMessageStart[0] = 0xf1;
    pchMessageStart[1] = 0x7a;
    pchMessageStart[2] = 0x7a;
    pchMessageStart[3] = 0x1f;
    nDefaultPort = 8337;
    nPruneAfterHeight = 100000;
    m_assumed_blockchain_size = 1;
    m_assumed_chain_state_size = 1;

    // Easy genesis for immediate launch (very low difficulty so nonce=0 is valid).
    // Re-mine a harder genesis later if desired.
    genesis = CreateGenesisBlock(1728835200, 0, 0x207fffff, 1, 50 * COIN);
    consensus.hashGenesisBlock = genesis.GetHash();
    // No asserts — hash is computed at runtime

    // No DNS seeds yet
    // vSeeds.emplace_back("seed.example.com");

    // Distinct Fizzlewick prefixes
    base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 35);
    base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 95);
    base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1, 163);
    base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
    base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

    bech32_hrp = "fizz";
    silent_payments_hrp = "spizz";

    vFixedSeeds.clear();

    fDefaultConsistencyChecks = false;
    m_is_mockable_chain = false;

    m_assumeutxo_data = {};

    chainTxData = ChainTxData{
        .nTime    = 0,
        .tx_count = 0,
        .dTxRate  = 0,
    };

    m_headers_sync_params = HeadersSyncParams{
        .commitment_period = 649,
        .redownload_buffer_size = 15400,
    };
}
```

Also remove the two Bitcoin-specific `script_flag_exceptions.emplace(...)` lines that appear near the top of the original `CMainParams` (they reference old Bitcoin block hashes).

After the edit the file should compile cleanly and support `-testnet`, `-regtest`, etc. again.

---

## 3. Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)

# Optional rename
cp build/src/bitcoind   build/src/fizzlewickd
cp build/src/bitcoin-cli build/src/fizzlewick-cli
```

---

## 4. Mainnet Configuration

Create `~/.fizzlewick/fizzlewick.conf`:

```
server=1
rpcuser=fizz
rpcpassword=wick-of-the-ancients
rpcport=8336
port=8337
daemon=1
txindex=1
fallbackfee=0.0001
# addnode=YOUR.PUBLIC.NODE.IP   # once you have one
```

**Do not** put `regtest=1`.

---

## 5. First Launch & Mine

```bash
# Start
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf

# Check
./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo

# Wallet + blocks
./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 100 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

---

## 6. Mining / tpool

Point tpool (or any sha256d miner) at:

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

Stratum port 3333 works as before once the node is serving templates.

---

## 7. Network Parameters (for reference)

| Parameter              | Value                          |
|------------------------|--------------------------------|
| Name                   | Fizzlewick                     |
| Ticker                 | FIZZ                           |
| Role                   | Public mainnet test platform   |
| PoW                    | sha256d                        |
| Magic bytes            | `f1 7a 7a 1f`                  |
| Default P2P port       | 8337                           |
| Default RPC port       | 8336                           |
| bech32 HRP             | `fizz`                         |
| Datadir                | `fizzlewick`                   |
| Genesis timestamp      | Wizard line (see above)        |
| Initial difficulty     | Easy (`0x207fffff`)            |
| Subsidy                | Poetic (base 50 ±20 triangle, period 2100 + slow decay) |

---

## 8. Verification Checklist

- [ ] `chainparams.cpp` compiles (all networks present)
- [ ] Node starts without `-regtest`
- [ ] `getblockchaininfo` shows chain = "main"
- [ ] Magic / port match the table above
- [ ] New address starts with `fizz1...` (or the base58 prefix)
- [ ] Can generate blocks and see balance increase
- [ ] tpool can connect and receive work

---

## 9. Optional Follow-ups (post-launch)

- Rename binaries / man pages to `fizzlewickd` / `fizzlewick-cli`
- Add one or more public seed nodes and DNS seeds
- Re-mine a higher-difficulty genesis if desired
- Simple block explorer
- Update any remaining docs that still mention regtest as primary

---

## 10. Design Stance (do not change)

- Strong but basic Bitcoin-family consensus
- Public test / play / integration platform
- No value claims, no monetary product language
- Prefer small, reviewable changes

---

**Handoff complete.**  
Once the single `chainparams.cpp` restore is done, the chain is ready to launch.

Questions → contact the repo owner (5mil).
