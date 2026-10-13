# Fizzlewick (FIZZ)

A Bitcoin-family chain launched as a **public mainnet test platform**.  
Straight clone of Bitcoin Core. **Strong, generally basic, intentionally un-fancy.**

Mined by tpool on sha256d. Not a monetary product and not an investment.  
People may do with the coins as they will.

*"Lo, another ledger of flickering wicks. Mine if you must, but mind the smoke."*  
— some second-rate ancient wizard, probably

## What this is

| Item | Value |
|------|--------|
| **Name** | Fizzlewick |
| **Ticker** | FIZZ |
| **Role** | Public mainnet test / play / integration platform |
| **PoW** | sha256d |
| **Architecture** | Straight Bitcoin Core fork. UTXO, headers, RPC shape preserved |
| **Datadir** | `fizzlewick` |
| **Mainnet P2P** | 8337 |
| **Mainnet RPC** | 8336 (configurable) |
| **Magic** | `f1 7a 7a 1f` |
| **bech32** | `fizz1...` |

Subsidy is **not** pure halvings — see poetic schedule below.

## Design stance

- **Strong but basic.** Reliable Bitcoin-family consensus, clear RPC, ordinary sha256d.
- **Public test platform.** Live mainnet for testing, experimentation, and whatever people choose to do with the coins.
- **Transparent ledger.** Same spirit as tpool.
- **No value claims.** Engineering / play target, not speculation.

## Poetic subsidy

One function: `GetBlockSubsidy` in `src/validation.cpp`.

- Base 50 FIZZ  
- Triangle-wave ±20 FIZZ, period 2100 blocks  
- Slow integer decay (~5% every 100 000 blocks)  
- Pure integer sats; no float consensus math  

| height | approx FIZZ |
|--------|-------------|
| 0 | 30 |
| 1050 | 70 |
| 2100 | 30 |
| 100000 | ~58 |
| 210000 | ~25 |

## Launch (mainnet)

See **LAUNCH.md** for conf, start, mine, and the exact tpool EXTERNAL RPC line.

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

## Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)
# then rename/symlink bitcoind → fizzlewickd as desired
```

The wick stays lit. The hash remains.
