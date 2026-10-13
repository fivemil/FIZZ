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

# 1. Mainnet identity + 2-minute blocks
git checkout master -- src/kernel/chainparams.cpp
git apply patches/fizzlewick_mainnet.patch

# 2. Coinbase maturity 20
git apply patches/fizzlewick_maturity.patch

# 3. Abolish dust (the hilarious one)
git apply patches/fizzlewick_dust.patch

# Commit
git add src/kernel/chainparams.cpp src/consensus/consensus.h src/policy/policy.h
git commit -m "mainnet: Fizzlewick — 2-min blocks, maturity 20, no dust"
```

Then build and run (sections 3–6).

---

## 1. Current Status

| Item | Status |
|------|--------|
| Poetic subsidy | Already on master |
| Docs | Updated on this branch |
| Mainnet identity + 2-min blocks | `patches/fizzlewick_mainnet.patch` |
| Coinbase maturity = 20 | `patches/fizzlewick_maturity.patch` |
| Dust abolished | `patches/fizzlewick_dust.patch` |
| Binary rename | Optional |
| Public seeds / explorer | Post-launch |

**Branch:** https://github.com/fivemil/FIZZ/tree/mainnet-launch

---

## 2. The three real improvements over Bitcoin

### A. 2-minute blocks
```cpp
consensus.nPowTargetSpacing = 2 * 60;  // the wick burns faster
```
Confirmations in minutes instead of tens of minutes.

### B. Coinbase maturity = 20
```cpp
// 20 blocks (~40 minutes at 2-min spacing). Bitcoin's 100 is pure friction for no good reason on a live chain.
inline constexpr int COINBASE_MATURITY = 20;
```
Bitcoin: ~16 hours before newly mined coins are spendable.  
Fizzlewick: ~40 minutes. Same model, usable chain.

### C. Dust abolished (the hilarious simple one)
```cpp
// Even the tiniest spark may light a wick. Dust is not refuse on this chain.
inline constexpr unsigned int DUST_RELAY_TX_FEE{1};
```
Bitcoin treats small outputs like toxic waste and rejects them.  
Fizzlewick lets 1-sat outputs live. One constant. Suddenly the chain is actually fun to play with.

---

## 3. Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)

cp build/src/bitcoind    build/src/fizzlewickd
cp build/src/bitcoin-cli build/src/fizzlewick-cli
```

---

## 4. Mainnet config

`~/.fizzlewick/fizzlewick.conf`:

```
server=1
rpcuser=fizz
rpcpassword=wick-of-the-ancients
rpcport=8336
port=8337
daemon=1
txindex=1
fallbackfee=0.0001
```

**No** `regtest=1`.

---

## 5. First launch & mine

```bash
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf

./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo

./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 25 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

---

## 6. Mining / tpool

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

---

## 7. Network parameters

| Parameter | Value |
|-----------|--------|
| Name | Fizzlewick |
| Ticker | FIZZ |
| Block time | **2 minutes** |
| Coinbase maturity | **20 blocks** |
| Dust relay fee | **1** (dust abolished) |
| Magic | `f1 7a 7a 1f` |
| P2P port | 8337 |
| RPC port | 8336 |
| bech32 | `fizz` |
| Subsidy | Poetic (triangle ±20 + slow decay) |

---

## 8. Verification checklist

- [ ] All three patches apply cleanly
- [ ] Compiles
- [ ] `getblockchaininfo` → `"chain": "main"`
- [ ] Addresses start with `fizz1...`
- [ ] Blocks ~ every 2 minutes under load
- [ ] Coinbase spendable after 20 blocks
- [ ] 1-sat outputs are accepted / relayed
- [ ] tpool receives work

---

## 9. Design stance (do not change)

- Strong but basic Bitcoin-family consensus
- Public test / play / integration platform
- No value claims
- Prefer small, reviewable changes

---

**Handoff complete.**  
Three patches → build → launch.  
The wick burns faster. Twenty is enough. Even the tiniest spark may light a wick.
