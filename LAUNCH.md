# Fizzlewick LAUNCH

Primary path: **regtest / local play**.  
This chain is kept alive as a stable testing target for tpool and other projects.

## 1. Conf

`~/.fizzlewick/fizzlewick.conf`:

```
regtest=1
server=1
rpcuser=fizz
rpcpassword=wick-of-the-ancients
rpcport=18446
port=18445
daemon=1
txindex=1
fallbackfee=0.0001
```

## 2. Start

```bash
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf
# or still-named bitcoind with -regtest -datadir=...
```

```bash
./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo
```

## 3. Wallet + mine

```bash
./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 10 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

## 4. tpool EXTERNAL

```
http://fizz:wick-of-the-ancients@127.0.0.1:18446
```

PoW is sha256d → stock miners and tpool stratum on port 3333 work once the node serves templates.

## Params

| Item | Value |
|------|--------|
| Name | Fizzlewick |
| Ticker | FIZZ |
| Role | Long-lived test chain |
| PoW | sha256d |
| P2P (regtest) | 18445 |
| RPC (regtest) | 18446 |
| Datadir | fizzlewick |
| Subsidy | base 50 ±20 triangle (period 2100) + slow decay |

The ledger stays open for testing.
