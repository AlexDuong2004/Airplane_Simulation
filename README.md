# Airline Reservation & Flight Simulation System (C++)


## Overview

The simulator loads a network of airports and flights from a text file, then lets a user search for a route between two airports. Routes may involve one or more connecting flights, so the core of the project is a graph search over the flight network that respects real-world constraints like layover timing.

## Features

- **Flight network modeling** : airports, inter-airport distances, and scheduled flights with departure times, capacity, and operating cost
- **Multi-segment itinerary search** : depth-first search across the flight graph to find valid connecting routes between any two airports, respecting minimum connection times
- **Airline financials** : passenger registration, itinerary pricing, and revenue/balance tracking
- **Custom console UI framework** : a lightweight, reusable set of UI widgets (buttons, text fields, labels, list boxes) built on the Observer pattern for event-driven updates
- **Data-driven configuration** : airports, distances, and flights are all loaded from a plain-text input file at runtime, so the simulation isn't hardcoded

## Design & Architecture

- **Observer pattern** (`ECObserver` / `ECObserverSubject`) drives UI refresh widgets subscribe to state changes instead of being polled
- **Singleton pattern** (`ECAirportInfo::Instance()`) provides a single source of truth for airport and distance data across the app
- **Separation of concerns** across distinct modules: ticketing/search (`ECAirlineTicketing`), financials (`ECAirlineFinancial`), flight/airport domain models (`ECFlight`, `ECAirport`, `ECFlightItinerary`), and a decoupled console UI layer (`ECConsoleUI*`)
- **Graph search algorithm**: itinerary search is implemented as a DFS over airports as nodes and flights as edges, building up valid multi-leg itineraries as it explores

## Tech Stack

- C++20
- Standard Library only (`<vector>`, `<map>`, `<set>`, `<string>`) — no third-party dependencies
- g++ / Make-free build (single compile command)

## Build & Run

```bash
g++ ECConsoleUIListBox.cpp ECConsoleUITextLabel.cpp ECTextViewImp.cpp \
    ECConsoleUIView.cpp TestProject.cpp ECAirlineFinancial.cpp \
    ECAirlineOperation.cpp ECAirlineSimulator.cpp ECAirlineTicketing.cpp \
    ECAirport.cpp ECFlight.cpp ECFlightItinerary.cpp ECConsoleUIButton.cpp \
    ECConsoleUITextField.cpp -o TestProject -std=c++20

./TestProject test_file.txt
```

## Input File Format

The simulator reads a plain-text file describing the flight network. Each line is a record. Lines starting with `#` are comments.

| Prefix | Record type | Fields |
|--------|-------------|--------|
| `1`    | Airport     | code, full name |
| `2`    | Distance    | origin code, destination code, distance (miles) |
| `3`    | Flight      | origin code, destination code, departure time, capacity, operating cost |

```
1 ORD Chicago
1 SFO San Francisco
2 ORD SFO 2000
3 ORD SFO 11.0 10 3000
```

## Project Structure

```
ECAirlineSimulator.{h,cpp}   # Top-level simulator: configuration + orchestration
ECAirlineTicketing.{h,cpp}   # Flight storage + DFS-based itinerary search
ECAirlineFinancial.{h,cpp}   # Pricing, passenger registration, revenue tracking
ECAirport.{h,cpp}            # Airport model + singleton airport/distance registry
ECFlight.{h,cpp}             # Single flight segment
ECFlightItinerary.{h,cpp}    # Multi-segment itinerary
ECObserver.h                 # Observer pattern base classes
ECConsoleUI*.{h,cpp}         # Reusable console UI widget framework (MVC-style)
TestProject.cpp              # Entry point / test driver
```
