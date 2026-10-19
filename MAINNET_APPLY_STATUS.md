# Mainnet apply status

**Date:** 19 October 2026

## Remote `mainnet-launch` (done via API)

- [x] `src/consensus/consensus.h` — `COINBASE_MATURITY = 20`
- [x] `src/policy/policy.h` — `DUST_RELAY_TX_FEE = 200`

## Still needed on remote

- [ ] `src/kernel/chainparams.cpp` — currently still `PLACEHOLDER_WILL_REPLACE`

The full Fizzlewick `chainparams.cpp` is ready (wizard genesis, magic `f1 7a 7a 1f`, port 8337, bech32 `fizz`, 2-min blocks, easy genesis, no seeds). Apply with:

```bash
git fetch origin && git checkout mainnet-launch
git checkout origin/master -- src/kernel/chainparams.cpp
# then re-apply identity edits from patches/fizzlewick_mainnet.patch
# OR copy the verified local file from the apply session
git add src/kernel/chainparams.cpp
git commit -m "mainnet: Fizzlewick chainparams (identity + 2-min blocks + easy genesis)"
git push
```

## After chainparams is on remote

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)
cp build/src/bitcoind build/src/fizzlewickd
cp build/src/bitcoin-cli build/src/fizzlewick-cli
# config + start per LAUNCH_HANDOFF.md
```
