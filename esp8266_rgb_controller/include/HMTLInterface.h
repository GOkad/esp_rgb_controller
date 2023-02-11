#ifndef HMTL_INTERFACE
#define HMTL_INTERFACE

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html><html><head> <meta name="viewport" content="width=device-width, initial-scale=1"/> <style>*{padding:0; margin:0; font-family: 'Arial';}body{background:#222; color:#fff; display: flex; flex-flow:column; row-gap: 20px; padding:10px;}.rgb-controller{border:1px solid #fff; border-radius: 5px; overflow: hidden; transition: all 0.2s linear}label{float:right; display: flex; flex-flow: column; width: 55%; background:#222; text-align: right; font-size: 1.2em; padding: 0 15px;}.rgb-controller:nth-child(odd) label{float:left; text-align: left;}label span{width: 100%; font-size: 2em;}.toast{position: fixed; bottom:10px; width: 94%; border:1px solid #fff; display: flex; border-radius: 5px; justify-content: space-between; background:#222;}.dismiss{border:none; font-size:1.2em; width: 50px; color: #fff; padding: 0 10px}.msg{padding: 5px 10px;}.toast.error{border-color: #f00;}.toast.success{border-color: #00cf00;}.toast.error button{background: #f00;}.toast.success button{background: #00cf00;}</style></head><body> <div> Access Point IP: 168.4.0.1 <br>Network IP: %LOCAL_NETWORK_IP% </div><script>const body=document.body; const SUCCESS="success"; const ERROR="error"; function toHex( srting_int ){let hex=parseInt(srting_int).toString(16); if (hex.length==1){hex="0" + hex;}return hex;}function toast(message, type){body.innerHTML +=` <div class="toast ${type}"> <span class="msg">${message}</span> <button class="dismiss" onclick="this.parentNode.parentNode.removeChild(this.parentNode);"> OK </button> </div>`;}function update_color(cont, color){cont.querySelector("label span").innerHTML=color; cont.style.borderColor=color; cont.style.background=color;}function request(url, callback, error_cb=()=>{}){fetch(url) .then(response=> response.json()) .then(data=> callback(data)) .catch( error=>{toast(error.message ? error.message : 'Something went wrong', ERROR ); error_cb();});}function build(){request('/get-data',(data)=>{data.forEach( controller=>{const{id,red,green,blue}=controller; const color='#'+toHex(red)+''+toHex(green)+''+toHex(blue); body.innerHTML +=` <div id='cont-${id}' class="rgb-controller" onclick="this.querySelector('input').click()" > <label> Controller: ${id}<span class="color">#${color}</span> </label> <input hidden="true" type="color" name="c${id}" value="${color}" onchange="update(this)"/> </div>`; update_color(body.querySelector('#cont-'+id),color);});});}function update(input){const color=input.value; const url=`/update-color?id=${input.name.replace('c','')}&`+ `red=${parseInt(color[1]+color[2], 16)}&`+ `green=${parseInt(color[3]+color[4], 16)}&`+ `blue=${parseInt(color[5]+color[6], 16)}`; console.log(url); request(url,(data)=>{update_color(input.parentNode, color);}, ()=>{alert("TODO: Revert to older value");});}build();</script></body></html>
)rawliteral";

#endif
