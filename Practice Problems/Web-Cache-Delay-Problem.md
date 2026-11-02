# Web Cache Delay and Game Protocol Design (worked solution)

## Given
* Access link rate = 2 Mbps
* Average object size = 200 Kbits
* Average request rate = 10 requests/s
* Internet delay (router to origin and back) = 1.5 s
* LAN delay = 10 ms
* Cache hit rate = 50 %
* Rule: if link utilisation exceeds 0.9, queuing delay is treated as infinite

## Without a cache
* Traffic on access link = 10 × 200 Kbits = 2 Mbps
* Utilisation = 2 / 2 = **100 %**
* Average delay = **infinite** (utilisation > 0.9, queues grow without bound)

## With a cache (50 % hit rate)
* Traffic on access link = 0.5 × 2 Mbps = 1 Mbps → utilisation **50 %**
* Transmission time of an object on the access link = 200 Kbits / 2 Mbps = 0.1 s
* Miss delay ≈ 1.5 s + 0.1 s = 1.6 s; hit delay ≈ 0.01 s
* Average delay ≈ 0.5 × 0.01 + 0.5 × 1.6 = **≈ 0.81 s**

## Summary
| Scenario | Access-link utilisation | Average delay |
|---|---|---|
| No cache | 100 % | infinite (1.6 s if queuing is ignored) |
| Cache, 50 % hits | 50 % | ≈ 0.805 s |

## Part 2: real-time multiplayer VR game
### Transport protocol
Use a hybrid design:
* **UDP** for continuous updates (positions, head and hand pose, voice). Low latency and no head-of-line blocking; a lost update is simply replaced by the next one.
* **A reliable channel** (TCP, or reliable messages on top of UDP) for events that must arrive once and in order: match events, inventory changes, purchases.
* **Encryption:** DTLS over UDP, TLS over TCP. QUIC combines both needs: it runs over UDP, is encrypted, and offers reliable streams alongside unreliable datagrams.

### Keeping state
* The **server holds the authoritative game state** (world, positions used for final decisions, inventory). This prevents cheating and keeps all players consistent.
* The client identifies itself with a **short-lived session token** (cookie or signed token); the server validates it and keeps per-session state.
* A fully stateless server would save memory but makes anti-cheat checks, reconciliation and rollback much harder.
* Heartbeats and reconnection handling let a client resume without inconsistencies.
