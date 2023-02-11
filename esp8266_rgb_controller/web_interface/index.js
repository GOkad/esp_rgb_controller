const body = document.body;
const SUCCESS = "success";
const ERROR = "error";

function toHex( srting_int ) {
    let hex = parseInt(srting_int).toString(16);
    if (hex.length == 1) {
        hex = "0" + hex;
    }
    return hex;
}
function toast(message, type) {
    body.innerHTML += `
    <div class="toast ${type}">
        <span class="msg">${message}</span>
        <button class="dismiss" onclick="this.parentNode.parentNode.removeChild(this.parentNode);">
            OK
        </button>
    </div>`;
}
function update_color(cont, color) {
    cont.querySelector("label span").innerHTML = color;
    cont.style.borderColor = color;
    cont.style.background = color;
}
function request(url, callback, error_cb = () => {}) {
    fetch(url)
    .then(response => response.json())
    .then(data => callback(data))
    .catch( error => {
        // console.log( error );
        toast(error.message ? error.message : 'Something went wrong', ERROR );
        error_cb();
    });
}

function build(){
    /**
     * TODO: Update data to inlude IP
     * {
     *  "ip": "network_ip",
     *  "ssid": "network ssid",
     *  "controllers": [
     *    {
     *      "id": "1",
     *      "red": "255",
     *      "green": "133",
     *      "blue": "12"
     *    },
     * ]
     * }
     */
    // Mock data
    // const data = [
        
    //     {
    //         "id": "2",
    //         "red": "0",
    //         "green": "255",
    //         "blue": "123"
    //     }
    // ];
    request('/get-data',(data) => {
        data.forEach( controller => {
            const {id,red,green,blue} = controller;
            const color = '#'+toHex(red)+''+toHex(green)+''+toHex(blue);
    
            body.innerHTML += `
            <div id='cont-${id}' class="rgb-controller"
                onclick="this.querySelector('input').click()"
            >
                <label>
                    Controller: ${id}
                    <span class="color">#${color}</span>
                </label>
                <input
                    hidden="true"
                    type="color" name="c${id}"
                    value="${color}"
                    onchange="update(this)"
                />
            </div>`;
            update_color(body.querySelector('#cont-'+id),color);
        });    
    });
}

function update(input) {

    const color = input.value;

    const url = `/update-color?id=${input.name.replace('c','')}&`+
    `red=${parseInt(color[1]+color[2], 16)}&`+
    `green=${parseInt(color[3]+color[4], 16)}&`+
    `blue=${parseInt(color[5]+color[6], 16)}`;

    console.log(url);
    request(url,(data) => {
        update_color(input.parentNode, color);
    }, () => {
        alert("TODO: Revert to older value");
    });
}

build();
// update(document.querySelector('input'));

// toast("test message", SUCCESS);