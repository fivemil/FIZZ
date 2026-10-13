# Fizzlewick LAUNCH (Mainnet)

**Mainnet is live as a public test platform.**  
People may do with the coins as they will.

## 1. Conf

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
# addnode=your.public.node.ip   # optional
```

(No `regtest=1`)

## 2. Start

```bash
./fizzlewickd -datadir=$HOME/.fizzlewick -conf=$HOME/.fizzlewick/fizzlewick.conf
# or still-named bitcoind with the same conf
```

```bash
./fizzlewick-cli -datadir=$HOME/.fizzlewick getblockchaininfo
```

## 3. Wallet + mine

```bash
./fizzlewick-cli -datadir=$HOME/.fizzlewick createwallet "wizard"
ADDR=$(./fizzlewick-cli -datadir=$HOME/.fizzlewick getnewaddress)
./fizzlewick-cli -datadir=$HOME/.fizzlewick generatetoaddress 100 "$ADDR"
./fizzlewick-cli -datadir=$HOME/.fizzlewick getbalance
```

## 4. tpool EXTERNAL

```
http://fizz:wick-of-the-ancients@127.0.0.1:8336
```

PoW is sha256d → stock miners and tpool stratum on port 3333 work once the node serves templates.

## Params

| Item | Value |
|------|--------|
| Name | Fizzlewick |
| Ticker | FIZZ |
| Role | Public mainnet test platform |
| PoW | sha256d |
| P2P | 8337 |
| RPC | 8336 |
| Magic | f1 7a 7a 1f |
| Datadir | fizzlewick |
| bech32 HRP | fizz |
| Subsidy | base 50 ±20 triangle (period 2100) + slow decay |
| Genesis | Easy difficulty for immediate launch (re-mine harder later if desired) |

The ledger is open.
