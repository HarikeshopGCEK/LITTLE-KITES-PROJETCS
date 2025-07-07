const channelID = "2778607";
const url = `https://api.thingspeak.com/channels/${channelID}/feeds.json?results=1`;

async function fetchData() {
    try {
        const response = await fetch(url);
        const data = await response.json();
        const feed = data.feeds[0];

        const soli1d1 = Number(feed.field1);
        const soli2d1 = Number(feed.field2);
        const soli3d1 = Number(feed.field3);
        const tempd1 = Number(feed.field4);
        const humd1 = Number(feed.field5);

        const display = `
          <div class="data-list">
            <div class="data-item">
              <span class="label">Soil Moisture 1</span>
              <span class="value">${soli1d1}</span>
            </div>
            <div class="data-item">
              <span class="label">Soil Moisture 2</span>
              <span class="value">${soli2d1}</span>
            </div>
            <div class="data-item">
              <span class="label">Soil Moisture 3</span>
              <span class="value">${soli3d1}</span>
            </div>
            <div class="data-item">
              <span class="label">Temperature</span>
              <span class="value">${tempd1} &deg;C</span>
            </div>
            <div class="data-item">
              <span class="label">Humidity</span>
              <span class="value">${humd1} %</span>
            </div>
          </div>
          <div class="timestamp">
            Last updated: ${new Date(feed.created_at).toLocaleString()}
          </div>
        `;
        document.getElementById("dataDisplay").innerHTML = display;
    } catch (err) {
        document.getElementById("dataDisplay").textContent = "Error loading data.";
    }
}

fetchData();
setInterval(fetchData, 5000);