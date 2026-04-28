# C++ Option Pricing Library

A modular C++ pricing library implementing three industry-standard models for valuing European and path-dependent options.

## Models Implemented

| Model | Method | Use case |
|-------|--------|----------|
| **Black-Scholes** | Closed-form analytical | European vanilla & digital options |
| **CRR Binomial Tree** | Discrete lattice (numerical + closed-form) | European vanilla & digital options |
| **Black-Scholes Monte Carlo** | Stochastic simulation | Vanilla & path-dependent (Asian) options |

## Option Types

- **Vanilla:** European Call, European Put
- **Digital (Binary):** Digital Call, Digital Put
- **Asian:** Asian Call, Asian Put (path-dependent, MC-priced)

## Architecture
Option (abstract base)
├── VanillaOption
│   ├── CallOption
│   └── PutOption
├── DigitalOption
│   ├── DigitalCallOption
│   └── DigitalPutOption
└── AsianOption
├── AsianCallOption
└── AsianPutOption
Pricers
├── BlackScholesPricer      — analytical pricing + delta for vanilla & digital
├── BlackScholesMCPricer    — Monte Carlo simulation with confidence intervals
└── CRRPricer               — binomial tree (recursive + closed-form formula)
BinaryTree<T>               — generic templated binary tree used by CRR

## Quick Start

### Build

```bash
make
./projet
```

### Example — Black-Scholes pricer

```cpp
double S0 = 95.0;   // spot price
double K  = 100.0;  // strike
double T  = 0.5;    // maturity (years)
double r  = 0.02;   // risk-free rate
double sigma = 0.2; // implied volatility

CallOption call(T, K);
BlackScholesPricer pricer(&call, S0, r, sigma);

std::cout << "Price: " << pricer()       << std::endl;
std::cout << "Delta: " << pricer.delta() << std::endl;
```

### Example — CRR Binomial Tree

```cpp
int N = 150; // tree depth
double U = exp(sigma * sqrt(T / N)) - 1.0;
double D = exp(-sigma * sqrt(T / N)) - 1.0;
double R = exp(r * T / N) - 1.0;

CRRPricer crr(&call, N, S0, U, D, R);
crr.compute();

std::cout << "CRR (numerical):    " << crr()     << std::endl;
std::cout << "CRR (closed-form):  " << crr(true) << std::endl;
```

### Example — Monte Carlo pricer with confidence interval

```cpp
BlackScholesMCPricer mc(&call, S0, r, sigma);
mc.generate(10000); // simulate 10,000 paths

std::cout << "MC Price: " << mc() << std::endl;

auto ci = mc.confidenceInterval();
std::cout << "95% CI: [" << ci[0] << ", " << ci[1] << "]" << std::endl;
```

## Convergence

As tree depth N → ∞, the CRR binomial price converges to the Black-Scholes analytical price — this is verified in `main.cpp` with N = 150 steps.

The Monte Carlo pricer includes a running confidence interval that tightens as more paths are generated via successive `generate()` calls.

## Requirements

- C++17 or later
- Standard library only (no external dependencies)

## Background

Built as part of the ESILV Financial Engineering curriculum. Covers the theoretical foundations of risk-neutral pricing, the Black-Scholes PDE, binomial lattice models (Cox-Ross-Rubinstein, 1979), and Monte Carlo methods for derivative pricing.
