// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
#include <unordered_map>

using namespace std;

struct xsr_state
{
  uint16_t pool[4];

  bool operator==(const xsr_state& other) const 
  {
    return pool[0] == other.pool[0] && pool[1] == other.pool[1] && pool[2] == other.pool[2]
           && pool[3] == other.pool[3];
  }
};

namespace std {
  template <> struct hash<xsr_state> {
    std::size_t operator()(const xsr_state& state) const {
      return state.pool[0] ^ state.pool[1] ^ state.pool[2] ^ state.pool[3];
    }
  };
}

uint16_t roll(uint16_t x, int k) { 
  return (x << k) | (x >> (64 - k)); 
}

//xorsiro**
uint16_t xorshiro(xsr_state* state) {
  uint16_t* s = state->pool;
  uint16_t const returnValue = roll(s[1] * 5, 7) * 9;
  uint16_t const t = s[1] << 17;

  s[2] ^= s[0];
  s[3] ^= s[1];
  s[1] ^= s[2];
  s[0] ^= s[3];

  s[2] ^= t;
  s[3] = roll(s[3], 45);

  return returnValue;
}

int main()
{ 
    unordered_map<xsr_state, uint32_t> stateMap;

    uint32_t id = 0, warmup = 0, periodic = 0;


	uint16_t seed, N, min, max;
    cin >> seed >> N >> min >> max;
    xsr_state state = xsr_state();

		state.pool[0] = N;
		state.pool[1] = seed;
        state.pool[2] = min;
        state.pool[3] = max;

        while (true) {
          if (stateMap.contains(state)) {
            warmup = stateMap[state];
            periodic = id - warmup;
            break;
          }

          stateMap.emplace(state, id);
          cout << xorshiro(&state) % max << endl;
          id++;
        }

        cout << "warmup length: " << warmup << endl;
        cout << "periodic length: " << periodic << endl;
}
