# Restore src/validation.cpp

A bulk edit briefly replaced this ~300KB file. Restore in two steps:

## 1. Put the original file back

From the repo root:

```bash
curl -sL https://raw.githubusercontent.com/fivemil/FIZZ/60afa0b8d71ff0959eac27fe73fadafe72b70cce/src/validation.cpp -o src/validation.cpp
```

That commit is the clean Bitcoin-derived tree before the clobber.

## 2. Apply the Fizzlewick poetic subsidy

Open `src/validation.cpp`, find:

```cpp
CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
```

Replace **the entire function** with the body in:

`GetBlockSubsidy.snippet.cpp`

(or copy from that file).

## 3. Commit

```bash
git add src/validation.cpp
git commit -m "consensus: Fizzlewick poetic GetBlockSubsidy"
git push
```

## Verify

```bash
grep -A5 "Fizzlewick poetic" src/validation.cpp
```

You should see the triangle-wave / slow-decay implementation.

Docs: README.md, LAUNCH.md, FIZZLEWICK.md
