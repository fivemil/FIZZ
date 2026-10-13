# Fizzlewick changes on this tree

This repo is a Bitcoin Core fork used as **Fizzlewick (FIZZ)** — a durable test chain for tpool and related work.

## Applied / to apply

1. **Poetic subsidy** — replace `GetBlockSubsidy` in `src/validation.cpp` with the body in `GetBlockSubsidy.snippet.cpp`.
2. **Identity (recommended next)**  
   - Binary / client name → Fizzlewick / fizzlewickd / fizzlewick-cli  
   - Datadir → `fizzlewick`  
   - Regtest ports → P2P 18445, RPC 18446  
   - Custom magic bytes  
   - Genesis message (wizard line) + re-mine genesis as needed  
3. **Docs** — `README.md`, `LAUNCH.md` describe the durable-test stance and how to point tpool at the node.

## Out of scope

No new consensus architecture. No value claims. Prefer small, reviewable changes.

Repo: https://github.com/fivemil/FIZZ  
Companion pool: https://github.com/5mil/tpool
