// Drop-in replacement for GetBlockSubsidy in src/validation.cpp
// Fizzlewick poetic subsidy — integer only, one clear function.

CAmount GetBlockSubsidy(int nHeight, const Consensus::Params& consensusParams)
{
    // Fizzlewick poetic subsidy — integer only, one clear function.
    //
    // A second-rate ancient wizard's reward: base 50 FIZZ that gently
    // rises and falls like a mumbled verse (triangle wave, period 2100
    // blocks) with amplitude 20 FIZZ, plus a slow long-term fade
    // (~5% every 100 000 blocks) so the spell eventually peters out.
    // No floating point. Auditable in one place.
    //
    // Sample (sats): h=0 → 30e8, h=1050 → 70e8, h=2100 → 30e8, ...
    // See LAUNCH.md for the printed schedule.

    const int PERIOD = 2100;
    const CAmount BASE = 50 * COIN;
    const CAmount AMP  = 20 * COIN;

    // Slow decay
    int epochs = nHeight / 100000;
    CAmount base = BASE;
    for (int i = 0; i < epochs && i < 40; ++i) {
        base = (base * 19) / 20;
    }

    int phase = nHeight % PERIOD;
    int half = PERIOD / 2;
    int t = (phase <= half) ? phase : (PERIOD - phase);
    CAmount wave = -AMP + (2 * AMP * static_cast<CAmount>(t)) / half;

    CAmount subsidy = base + wave;
    if (subsidy < 0) subsidy = 0;
    // consensusParams is unused; kept for call-site compatibility
    (void)consensusParams;
    return subsidy;
}
