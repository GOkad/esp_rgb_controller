#ifndef HMTL_INTERFACE
#define HMTL_INTERFACE

const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
<html>
<head>
    <style>
        * {
            padding:0;
            font-size: 1em;
        }
        body {
            background: #000;
            color:#fff;
        }
        .rgb-controller {
            border:1px solid #fff;
            display: flex;
            flex-flow: column;
            row-gap: 15px;
            padding:10px 
        }
        input {
            height: 100px;
            width:100%;
        }
        button {
            padding: 10px 0;
            width:100%;
            background: #000;
            color: #fff;
            border:1px solid #fff;
            border-radius: 5px;
        }
    </style>
</head>
<body>
    <div id="error"></div>
    <div id="main">
        RGB Controlls
    </div>

    <script>
        const errorContainer = document.querySelector('#error')
        const main = document.querySelector('#main');

        function request(url, cb) {
            fetch(url)
            .then((response) => response.json())
            .then((data) => cb(data))
            .catch((error) => {
                console.error( error );
                displayError(JSON.stringify(error));
            });
        }

        function displayError(error) {
            errorContainer.innerHTML = error;
        }

        function toHex( int ) {
            let hex = int.toString(16);
            if (hex.length == 1) {
                hex = "0" + hex;
            }
            return hex;
        }

        function build() {
            request('/get', (data) => {
                main.innerHTML = '';
                data.forEach((controller)=>{
                    console.log(controller, main);
                    const hexColor = toHex(controller.red)+''+toHex(controller.green)+''+toHex(controller.blue);

                    main.innerHTML += `
                        <div class='rgb-controller'>
                            ${controller.id}
                            <input
                                type='color'
                                name='${controller.id}'
                                value='#${hexColor}'
                            >
                            <button onclick='update(this.parentNode)'>
                                Update
                            </button>
                        </div>
                    `;
                });
            });

            // document.querySelector('.rgb-controller button').click();
        }

        function update(cont) {
            const input = cont.querySelector("input");
            const color = input.value;

            const url = `/update?id=${input.name}&`+
                `red=${parseInt(color[1]+color[2], 16)}&`+
                `green=${parseInt(color[3]+color[4], 16)}&`+
                `blue=${parseInt(color[5]+color[6], 16)}`;
            
                console.log(url);
            request(url,(data) => {
                console.log(data);
            });
        }

        build();
    </script>
</body>
</html>
)rawliteral";

#endif
