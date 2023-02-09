const errorContainer = document.querySelector('#error')
const main = document.querySelector('#main');

function request(url, cb) {
    fetch(url)
    .then((response) => response.json())
    .then((data) => cb(data))
    .catch((error) => {
        console.error( error );
        displayError(error.message());
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
    // request('/get', (data) => {
        main.innerHTML = '';
        const data = [
            {
                'id': 'ID',
                'r': 255,
                'g': 55,
                'b': 127,
            }
        ];
        data.forEach((controller)=>{
            console.log(controller, main);
            const hexColor = toHex(controller.r)+''+toHex(controller.g)+''+toHex(controller.b);

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
    // });
}

function update(container) {

}

build();