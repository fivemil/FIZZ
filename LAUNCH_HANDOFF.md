# Fizzlewick (FIZZ) Mainnet Launch Handoff

**Date:** 13 October 2026  
**Branch:** `mainnet-launch`  
**Repo:** https://github.com/fivemil/FIZZ  
**Companion pool:** https://github.com/5mil/tpool  

**Goal:** Launch Fizzlewick as a public mainnet test platform today.  
People may do with the coins as they will. This is **not** a monetary product and carries no value claims.

---

## Quick Start (copy-paste)

```bash
git fetch origin
git checkout mainnet-launch
git checkout master -- src/kernel/chainparams.cpp
git apply patches/fizzlewick_mainnet.patch
# verify it applied cleanly, then:
git add src/kernel/chainparams.cpp
git commit -m "mainnet: apply Fizzlewick chainparams"
```

Then build and run (sections 3–6 below).

---

## 1. Current Status

| Item | Status |
|------|--------|
| Poetic subsidy (`GetBlockSubsidy`) | Already on master |
| Docs (README / LAUNCH / FIZZLEWICK) | Updated on this branch |
| Mainnet identity changes | Clean patch ready |
| Patch file | `patches/fizzlewick_mainnet.patch` |
| Binary rename | Optional |
| Public seeds / explorer | Post-launch |

**Branch:** https://github.com/fivemil/FIZZ/tree/mainnet-launch

---

## 2. Apply the chainparams fix

```bash
git checkout mainnet-launch
git checkout master -- src/kernel/chainparams.cpp   # restore full original
git apply patches/fizzlewick_mainnet.patch          # apply Fizzlewick changes
```

The patch only touches `CMainParams` and the shared genesis timestamp.  
All other networks (TestNet, RegTest, SigNet) and factory functions remain intact.

### What the patch changes

| Item | Value |
|------|--------|
| Genesis timestamp | Wizard line |
| Magic bytes | `f1 7a 7a 1f` |
| Default P2P port | `8337` |
| bech32 HRP | `fizz` |
| Address prefixes | Distinct (not Bitcoin) |
| Initial difficulty | Easy (`0x207fffff`) — nonce 0 works |
| BIP activation | From height 1 |
| Seeds / assumeutxo / min-chainwork | Cleared |
| `fPowAllowMinDifficultyBlocks` | `true` |

After applying, commit the result on this branch (or open a PR to master).

---

## 3. Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)

# Optional but recommended
cp build/src/bitcoind    build/src/fizzlewickd
cp build/src/bitcoin-cli build/src/fizzlewick-cli
```

---

## 4. Mainnet config

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
# addnode=YOUR.PUBLIC.NODE.IP
```

**Do not** set `regtest=1`.

---

## 5. First launch & mine

```bash
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf

./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo

./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 100 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

---

## 6. Mining / tpool

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

Stratum on port 3333 works once the node is serving templates.

---

## 7. Network parameters

| Parameter | Value |
|-----------|--------|
| Name | Fizzlewick |
| Ticker | FIZZ |
| Role | Public mainnet test platform |
| PoW | sha256d |
| Magic | `f1 7a 7a 1f` |
| P2P port | 8337 |
| RPC port | 8336 |
| bech32 | `fizz` |
| Datadir | `fizzlewick` |
| Subsidy | Poetic (base 50 ±20 triangle, period 2100 + slow decay) |

---

## 8. Verification checklist

- [ ] `git apply patches/fizzlewick_mainnet.patch` succeeds with no rejects
- [ ] Project compiles cleanly
- [ ] Node starts without `-regtest`
- [ ] `getblockchaininfo` → `"chain": "main"`
- [ ] New addresses begin with `fizz1...`
- [ ] Blocks can be generated and balance increases
- [ ] tpool connects and receives work

---

## 9. Optional follow-ups

- Rename binaries / man pages to `fizzlewickd` / `fizzlewick-cli`
- Add public seed nodes and DNS seeds
- Re-mine a harder genesis if desired
- Simple block explorer

---

## 10. Design stance (do not change)

- Strong but basic Bitcoin-family consensus
- Public test / play / integration platform
- No value claims
- Prefer small, reviewable changes

---

**Handoff complete.**  
Apply the patch → build → launch.  
Questions → repo owner (5mil).
