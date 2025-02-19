function reservoirSampling(stream, k) {
  const reservoir = [];
  let i = 0;

  for(const item of stream) {
    if(i < k) {
      reservoir.push(item);
    } else {
      const j = Math.floor(Math.random() * i);
      if(j < k) {
        reservoir[j] = item;
      }
    }
    i++;
  }
  return reservoir;
}

// example usage
const stream = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
const k = 5;

const sample = reservoirSampling(stream, k);
console.log(sample);

function* numberStream(n) {
  for(let i = 1; i <= n; i++) {
    yield i;
  }
}

const largeStream = numberStream(100);
const largeSample = reservoirSampling(largeStream, 10);
console.log(largeSample);

// ex with infinite stream
function* infiniteStream() {
  let i = 1;
  while(true) {
    yield i++;
  }
}

const infinite = infiniteStream();
const sampleFromInfinite = reservoirSampling(infinite, 5);
console.log(sampleFromInfinite);

const emptyStream = [];
const emptySample = reservoirSampling(emptyStream, 3);
console.log(emptySample);

const shortStream = [1, 2, 3];
const largeK = 5;
const shortSample = reservoirSampling(shortStream, largeK);
console.log(shortSample);
