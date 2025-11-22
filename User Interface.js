const GRID_SIZE = 5;
const TOTAL_SHARDS = GRID_SIZE * GRID_SIZE;
const CONTAINER  = document.getElementById('fragment-container');
const STATUS = document.getElementById('status-message');
function getRandomColor() {
    const r = Math.floor(Math.random() * 256);
    const g = Math.floor(Math.random() * 256);
    const b = Math.floor(Math.random() * 256);
    return 'rgb(${r}, ${g}, ${b})';
}
function intializeFragments(){
CONTAINER.innerHTML = ''; 
for (let i = 0; i < TOTAL_SHARDS; i++) {
     const shard = document.createElement('div');
      shard.className = 'shard'; 
      shard.id = `shard-${i}`;
       shard.style.backgroundColor = getRandomColor();
        shard.textContent = `ID ${i}`; 
        CONTAINER.appendChild(shard);
     }
     }
     function getCorrectColor(x, y) {
         const red = Math.floor((GRID_SIZE - 1 - x) / (GRID_SIZE - 1) * 255); 
         const green = Math.floor((GRID_SIZE - 1 - y) / (GRID_SIZE - 1) * 255); 
         const blue = Math.floor((x + y) / (2 * (GRID_SIZE - 1)) * 255);
          return `rgb(${red}, ${green}, ${blue})`;
         }
           async function simulateAssembly() {
             STATUS.textContent = " Analyzing thousands of data fragments using Greedy and Genetic Algorithms..."; 
             await new Promise(resolve => setTimeout(resolve, 3000));
              STATUS.textContent = "Assembly Complete! Rebuilding image for Visual Verification...";
    for (let y = 0; y < GRID_SIZE; y++) {
    for (let x = 0; x < GRID_SIZE; x++) { 
        const shardIndex = y * GRID_SIZE + x; 
        const shardElement = document.getElementById(`shard-${shardIndex}`);
        shardElement.style.backgroundColor = getCorrectColor(x, y); 
        shardElement.textContent = `(${x}, ${y})`;
     }
     } 
     STATUS.textContent = " Data Integrity Restored! Visual Verification Successful.";
     }
