# Fizzlewick (FIZZ)

A durable Bitcoin-family test chain kept alive for ongoing work on [tpool](https://github.com/5mil/tpool) and other projects.  
Straight clone of Bitcoin Core. **Strong, generally basic, intentionally un-fancy.**

Mined by tpool on sha256d / port 3333. Not a monetary product and not an investment.

*"Lo, another ledger of flickering wicks. Mine if you must, but mind the smoke."*  
— some second-rate ancient wizard, probably

## What this is

| Item | Value |
|------|--------|
| **Name** | Fizzlewick |
| **Ticker** | FIZZ |
| **Role** | Long-lived test / play / integration chain |
| **PoW** | sha256d |
| **Architecture** | Straight Bitcoin Core fork. UTXO, headers, RPC shape preserved |
| **Datadir** | `fizzlewick` |
| **Ports (regtest)** | P2P 18445, RPC 18446 |

Subsidy is **not** pure halvings — see poetic schedule below.

## Design stance

- **Strong but basic.** Reliable Bitcoin-family consensus, clear RPC, ordinary sha256d.
- **Perpetual for testing.** Live tests beat spinning up ephemeral regtest every time.
- **Transparent ledger.** Same spirit as tpool.
- **No value claims.** Engineering target, not speculation.

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

Apply with the snippet in `GetBlockSubsidy.snippet.cpp` (or the patch in this commit if validation.cpp was updated).

## Launch

See **LAUNCH.md** for conf, start, mine, and the exact tpool EXTERNAL RPC line.

```
http://fizz:wick-of-the-ancients@127.0.0.1:18446
```

## Build

```bash
cmake -B build -DBUILD_GUI=OFF -DWITH_ZMQ=OFF
cmake --build build -j$(nproc)
# then rename/symlink bitcoind → fizzlewickd as desired
```

The wick stays lit. The hash remains.
