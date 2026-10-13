# Fizzlewick changes on this tree

This repo is a Bitcoin Core fork used as **Fizzlewick (FIZZ)** — a durable test chain for tpool and related work.

Repo: https://github.com/fivemil/FIZZ  
Companion pool: https://github.com/5mil/tpool

## Applied

1. **Poetic subsidy** — `GetBlockSubsidy` in `src/validation.cpp` is the integer triangle-wave + slow-decay function (base 50 FIZZ ±20, period 2100). See `GetBlockSubsidy.snippet.cpp` for the canonical body.
2. **Docs** — `README.md`, `LAUNCH.md` describe the durable-test stance and how to point tpool at the node.

## Still useful next (identity polish)

- Binary / client name → Fizzlewick / fizzlewickd / fizzlewick-cli  
- Datadir → `fizzlewick`  
- Regtest ports → P2P 18445, RPC 18446  
- Custom magic bytes  
- Genesis message (wizard line) + re-mine genesis as needed  

## Out of scope

No new consensus architecture. No value claims. Prefer small, reviewable changes.
