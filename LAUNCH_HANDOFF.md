# Fizzlewick (FIZZ) Mainnet Launch Handoff

**Date:** 13 October 2026  
**Branch:** `mainnet-launch`  
**Repo:** https://github.com/fivemil/FIZZ  
**Companion pool:** https://github.com/5mil/tpool  

**Goal:** Launch Fizzlewick as a public mainnet test platform today.  
People may do with the coins as they will. This is **not** a monetary product and carries no value claims.

---

## Quick Start

```bash
git fetch origin
git checkout mainnet-launch

git checkout master -- src/kernel/chainparams.cpp
git apply patches/fizzlewick_mainnet.patch
git apply patches/fizzlewick_maturity.patch
git apply patches/fizzlewick_dust.patch

git add src/kernel/chainparams.cpp src/consensus/consensus.h src/policy/policy.h
git commit -m "mainnet: Fizzlewick — 2-min blocks, 1-day retarget, maturity 20, sensible dust"
```

Then build and run (sections below).

---

## Implemented Improvements (from the deep list)

| # | Improvement | Status | How |
|---|-------------|--------|-----|
| 1 | 2-minute blocks + faster difficulty adjustment | **Done** | `nPowTargetSpacing = 2*60`, `nPowTargetTimespan = 1 day` |
| 2 | Coinbase maturity = 20 | **Done** | `COINBASE_MATURITY = 20` |
| 3 | Easy bootstrap period | **Done** | `fPowAllowMinDifficultyBlocks = true` + easy genesis |
| 4 | Explicit chain identity | **Done** | Unique magic `f1 7a 7a 1f`, bech32 `fizz`, distinct prefixes, wizard genesis message |
| 5 | Reject non-standard earlier | Partial | Modern script flags from height 1; further tightening is future work |
| 6 | Time-to-spendable awareness | Future | Wallet/RPC enhancement (not in these patches) |
| 7 | Strict modern BIPs from height 1 | **Done** | BIP34/65/66/CSV/Segwit active at 1 |
| 8 | Non-colliding names/ports/datadir | **Done** (docs + ports) | Port 8337/8336, datadir `fizzlewick`, recommended binary names |
| 9 | No Bitcoin seeds — intentional networking | **Done** | All vSeeds and fixed seeds cleared |
| 10 | Transparent poetic subsidy | **Done** (source) | Already in `GetBlockSubsidy`; surface more in RPC later |

---

## Network Parameters

| Parameter | Value |
|-----------|--------|
| Name | Fizzlewick |
| Ticker | FIZZ |
| Block time | **2 minutes** |
| Difficulty retarget | **1 day** |
| Coinbase maturity | **20 blocks** (~40 min) |
| Dust relay fee | **200** (playful, still anti-spam) |
| Magic | `f1 7a 7a 1f` |
| P2P / RPC | 8337 / 8336 |
| bech32 | `fizz` |
| Seeds | None (use `addnode`) |
| Subsidy | Poetic triangle ±20 + slow decay |

---

## Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)
cp build/src/bitcoind    build/src/fizzlewickd
cp build/src/bitcoin-cli build/src/fizzlewick-cli
```

---

## Config (`~/.fizzlewick/fizzlewick.conf`)

```
server=1
rpcuser=fizz
rpcpassword=wick-of-the-ancients
rpcport=8336
port=8337
daemon=1
txindex=1
fallbackfee=0.0001
# addnode=YOUR.PUBLIC.NODE.IP
```

**No** `regtest=1`.

---

## First Launch

```bash
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf
./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo
./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 25 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

---

## Mining / tpool

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

---

## Verification Checklist

- [ ] All three patches apply cleanly
- [ ] Compiles
- [ ] `getblockchaininfo` → `"chain": "main"`
- [ ] Addresses start with `fizz1...`
- [ ] Blocks arrive ~ every 2 minutes
- [ ] Difficulty can adjust after ~1 day of blocks
- [ ] Coinbase spendable after 20 blocks
- [ ] No Bitcoin seeds present
- [ ] tpool receives work

---

## Design Stance

- Strong but basic Bitcoin-family consensus
- Public test / play / integration platform
- No value claims
- Prefer small, reviewable changes

---

**Handoff complete.**  
Three patches cover the high-leverage items from the list of ten.  
The wick burns faster. Twenty is enough. Difficulty pays attention. Identity is unambiguous.
