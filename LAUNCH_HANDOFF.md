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
| Mainnet identity changes | Ready as a clean patch |
| Patch file | `patches/fizzlewick_mainnet.patch` |
| Binary rename / client branding | Optional |
| Public seeds / explorer | Post-launch |

**Branch URL:** https://github.com/fivemil/FIZZ/tree/mainnet-launch

---

## 2. Fix chainparams.cpp (one command)

The complete, correct `src/kernel/chainparams.cpp` is produced by applying the patch on top of master:

```bash
git fetch origin
git checkout mainnet-launch
git checkout master -- src/kernel/chainparams.cpp
git apply patches/fizzlewick_mainnet.patch
```

That is all. The patch changes only `CMainParams` + the shared genesis timestamp. All other networks (TestNet, RegTest, SigNet, factories) stay intact and the tree will compile.

### What the patch does

- Genesis timestamp → wizard line
- Magic bytes → `f1 7a 7a 1f`
- Default port → 8337
- bech32 HRP → `fizz`
- Distinct base58 prefixes
- Easy initial difficulty (`0x207fffff`) so nonce=0 is valid
- BIP features active from height 1
- Cleared Bitcoin seeds, assumeutxo, min-chainwork, historical exceptions
- `fPowAllowMinDifficultyBlocks = true`

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

## 7. Network Parameters

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
| Genesis timestamp      | Wizard line                    |
| Initial difficulty     | Easy (`0x207fffff`)            |
| Subsidy                | Poetic (base 50 ±20 triangle, period 2100 + slow decay) |

---

## 8. Verification Checklist

- [ ] `git apply patches/fizzlewick_mainnet.patch` succeeds cleanly
- [ ] Project compiles
- [ ] Node starts without `-regtest`
- [ ] `getblockchaininfo` shows chain = "main"
- [ ] New address starts with `fizz1...`
- [ ] Can generate blocks and see balance increase
- [ ] tpool can connect and receive work

---

## 9. Optional Follow-ups (post-launch)

- Rename binaries to `fizzlewickd` / `fizzlewick-cli`
- Add public seed nodes / DNS seeds
- Re-mine a higher-difficulty genesis if desired
- Simple block explorer

---

## 10. Design Stance (do not change)

- Strong but basic Bitcoin-family consensus
- Public test / play / integration platform
- No value claims
- Prefer small, reviewable changes

---

**Handoff complete.**  
One patch application and the chain is ready to launch.
