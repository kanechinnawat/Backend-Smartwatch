const char PAGE_MAIN[] PROGMEM = R"=====(<!DOCTYPE html><html>
<head>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="icon" href="data:,">
    <title>PNEUMA Config</title>
    <style>
        body {font-family: Arial, sans-serif;margin: 0;padding: 0;background-color: #f0f0f0;}
        div {margin: 5px auto;padding: 20px;width: 80%;background-color: #fff;border-radius: 5px;box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);}
        h1 {margin: 0;padding: 0;color: #333;}
        h2 {margin: 0;padding: 0;color: #666;}
        p {font-size: 0.8rem;}
        h5 {margin: 5px;}
        button {padding: 10px 20px;background-color: #666;color: #fff;border: none;border-radius: 5px;cursor: pointer;}
        input {padding: 5px;border: 1px solid #ccc;border-radius: 5px;}
        td {height: 40px;vertical-align: top;}
    </style>
</head>
<body>
    <div><h1>PNEUMA</h1><h2>Configuration</h2></div>
    <div>
        <h3>Add Wi-Fi config</h3>
        <table>
        <tr>
          <td><h5>SSID: </h5></td>
          <td><input type="text" name="ssid" id="s"></td>
        </tr>
        <tr>
          <td><h5>Password: </h5></td>
          <td><input type="password" name="pass" id="p"><p><input type="checkbox" onclick="showpass()">Show password</p></td>
        </tr>
        </table>
        <button onclick="submit()" id="sm">Submit</button>
    </div>
    <script>
        var xhr = new XMLHttpRequest();
        function addElement(i) {
            const currentDiv = document.getElementById("network_list");
            const newDiv = document.createElement("p");
            newDiv.append(i);
            currentDiv.append(newDiv);}
        function createwifilist(l) {
            const element = document.getElementById("wifilist");
            while (element.firstChild) {
              element.removeChild(element.firstChild);}
            console.log(l);
            for (let i = 0; i < l.length; i++) {
                console.log(l[i]["SSID"]);
                addElement(l[i]["SSID"]);}}
        function scan_wifi() {
            fetch('/scan')
                .then(res => res.json())
                .then(list => createwifilist(list["wifilist"]));}
        function showpass() {
            var p = document.getElementById("p");
            if (p.type === "password") {
                p.type = "text";
            } else {
                p.type = "password";}}
        function submit() {
            var s = document.getElementById("s").value;
            var p = document.getElementById("p").value;
            if ((s.length > 0) && (p.length >= 8) && (p.length <= 20)) {
                alert("Saved your config. ESP will reset to boot into new wifi.");
                xhr.open("POST", "/setting?ssid=" + s + "&pass=" + p, true);
                xhr.send();
            } else {
                alert("Error : password length must be of 8-20.");}}
    </script></body></html>)=====";