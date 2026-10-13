# Fizzlewick changes on this tree

This repo is a Bitcoin Core fork used as **Fizzlewick (FIZZ)** — now launched as a public mainnet test platform.

Repo: https://github.com/fivemil/FIZZ  
Companion pool: https://github.com/5mil/tpool

## Applied

1. **Poetic subsidy** — `GetBlockSubsidy` in `src/validation.cpp` is the integer triangle-wave + slow-decay function (base 50 FIZZ ±20, period 2100). See `GetBlockSubsidy.snippet.cpp` for the canonical body.
2. **Mainnet identity** (this launch):
   - Magic bytes: `f1 7a 7a 1f`
   - Default P2P port: 8337
   - bech32 HRP: `fizz`
   - Distinct base58 prefixes
   - New genesis timestamp (wizard line)
   - Easy initial difficulty so the chain starts immediately
   - BIP activations from height 1
   - Cleared Bitcoin seeds / assumeutxo / min-chainwork
3. **Docs** — README.md, LAUNCH.md updated for mainnet.

## Still useful next

- Binary / client name → fizzlewickd / fizzlewick-cli
- Public DNS seeds / fixed seeds once nodes are up
- Optional harder genesis re-mine
- Block explorer

## Out of scope

No new consensus architecture. No value claims. Prefer small, reviewable changes.
