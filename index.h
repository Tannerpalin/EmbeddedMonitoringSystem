const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style>
.card{
    max-width: 100%;
     min-height: 100%;
     background: #0e0101;
     box-sizing: border-box;
     color: #FFF;
     padding: 30px;
     margin:20px;
}
</style>
<body>

<div class="card">
  <h2>IoT Battery Monitor v1.1<br>
  Designed by Tanner Palin</h2><br>
  <h1 style="text-align:center;">Batteries: <span id="ADCValue">0</span></h1><br>
</div>
<script>

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 10000); //2000mSeconds update rate

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
