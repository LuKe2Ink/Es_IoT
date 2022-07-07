const axios = require('axios')

var i = 0

var temp;
var bright;

var led1;
var led2;
var led3;
var led4;

var irrigazione;


setInterval(async function () {
    i++
    //const response = await axios.post("http://10.201.101.150:3000/garden/boardsensor", );
    const response = await axios.post("http://localhost:3000/garden/dashboard", );

    console.log(response.data.led1)
    
    //temp = response.temp; //o response[0]
    //document.getElementById("cazzo").innerText = "ciao"+i;
    //bright = response.bright;
    //document.getElementById("cazzo").innerText = "ciao"+i;
    //
    //led1 = response.led1;
    //if(led1 == 1){
    //    document.getElementById("led1").style.color = "green";
    //} else {
    //    document.getElementById("led1").style.color = "red";
    //}
    //led2 = response.led2;
    //if(led1 == 1){
    //    document.getElementById("led2").style.color = "green";
    //} else {
    //    document.getElementById("led2").style.color = "red";
    //}
    //
    //led3 = response.led3;
    //document.getElementById("led3").innerText = led3;
    //led4 = response.led4;
    //document.getElementById("led4").innerText = led4;
    //
    //irrigazione = response.water;
    //document.getElementById("water").innerText = irrigazione;
    //
    
}, 5000);