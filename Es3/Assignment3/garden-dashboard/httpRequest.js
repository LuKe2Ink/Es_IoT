const axios = require('axios')

let gardenObject;

setInterval(async function () {
    //const response = await axios.post("http://10.201.101.150:3000/garden/boardsensor", );
    const response = await axios.get("http://localhost:3000/garden/dashboard");

    console.log(response.data)
    gardenObject = response.data;

    if(gardenObject.temp){
        
        var loading = document.getElementById("loading");
        if(loading.style.display != "none") {
            loading.style.display = "none"
            document.getElementById("data").style.display = "block";
        }

        temp = gardenObject.temp; //o gardenObject[0]
        document.getElementById("temperature").innerText = temp +"°C";
        bright = gardenObject.bright;
        document.getElementById("brightness").innerText = bright;
        
        if(gardenObject.led1){
           document.getElementById("led1").innerText = "Led on";
           document.getElementById("bulbLed1").src = "./src/on.png";
        } else {
           document.getElementById("led1").innerText = "Led off";
           document.getElementById("bulbLed1").src = "./src/off.png";
        }
        if(gardenObject.led2){
           document.getElementById("led2").innerText = "Led on";
           document.getElementById("bulbLed2").src = "./src/on.png";
        } else {
           document.getElementById("led2").innerText = "Led off";
           document.getElementById("bulbLed2").src = "./src/off.png";
        }
        
        console.log(typeof gardenObject.led3)
        if(gardenObject.led3 >= 1){
            document.getElementById("led3").innerText = "Led on at "+ gardenObject.led3;
            document.getElementById("bulbLed3").src = "./src/on.png";
         } else {
            document.getElementById("led3").innerText = "Led off";
            document.getElementById("bulbLed3").src = "./src/off.png";
         }
        if(gardenObject.led4 >= 1){
            document.getElementById("led4").innerText = "Led on at "+ gardenObject.led4;
            document.getElementById("bulbLed4").src = "./src/on.png";
         } else {
            document.getElementById("led4").innerText = "Led off";
            document.getElementById("bulbLed4").src = "./src/off.png";
         }
        
        document.getElementById("water").innerText = gardenObject.water;
        document.getElementById("state").innerText = gardenObject.state;
    }
    
    
    
}, 5000);