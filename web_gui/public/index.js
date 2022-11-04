const gui = document.body;
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const overlay = document.getElementById('overlay');
const title = document.getElementById('title');
const toolbar = document.getElementById('toolbar');

// template fetch function
let doFetch = async function fetcher(route, method, body, err) {
    let args = {
        method: method,
        headers: {
            'Content-Type': 'application/json'
        }
    }

    if (body != null) {
        args.body = JSON.stringify(body)
    }
    
    return fetch(route, args)
    .then(res => {
        if (res.ok) {
            return res.json()
        }
        else {
            throw new Error(err)
        }
    }).then(res => {
        return res
    })
}

// Get the mouse coordinates and send them to serial monitor
function mouseCoords(event) {
    let mouseX = event.pageX;
    let mouseY = event.pageY;

    let mouse = {
        x: mouseX,
        y: mouseY
    }

    // console.log(mouse)

    doFetch('/mouse', 'POST', mouse, 'Unable to send mouse coords')
}

function sizeCanvas() {
    canvas.width = window.innerWidth;
    canvas.height = gui.offsetHeight - toolbar.offsetHeight;
}

sizeCanvas();

canvas.addEventListener("mousemove", mouseCoords, false);

// Maintain drawings on screen when window is resized
window.addEventListener('resize', () => {
    sizeCanvas();

    if (canvas.getContext) {
        // const ctx = canvas.getContext('2d');
        for (let i = 0; i < clickPoints.length; i++) {
            ctx.beginPath();
            ctx.arc(clickPoints[i].x, clickPoints[i].y, 30, 0, 2 * Math.PI);
            ctx.fill();
        }
    }
})

let clickPoints = [];

function draw() {
    ctx.beginPath();
    if (clickPoints.length > 1) {
        ctx.moveTo(clickPoints[0].x, clickPoints[0].y);

        // for each click point make a shape
        for (let i = 1; i < clickPoints.length; i++) {
            ctx.lineTo(clickPoints[i].x, clickPoints[i].y);
            ctx.fill()
        }
    }
}

canvas.addEventListener("click", (event) => {
    let click = {
        x: event.clientX,
        y: event.clientY - toolbar.offsetHeight
    };
    clickPoints.push(click);

    if (canvas.getContext) {
        // append div to screen that looks like a circle at click point
        let effect = document.createElement('div');
        effect.className = 'effect';
        effect.style.left = String(click.x - 25) + 'px';
        effect.style.top = String(click.y - 25) + 'px';

        let fxSelector = document.getElementById('fxSelector');
        let fxName = fxSelector.options[fxSelector.selectedIndex].text; 

        let effectText = document.createElement('span');
        effectText.innerHTML = fxName;

        effect.appendChild(effectText);
        overlay.appendChild(effect);
        
        // initialize drawing canvas
        // const ctx = canvas.getContext('2d');
        // ctx.beginPath();


        // ctx.arc(click.x, click.y, 30, 0, 2 * Math.PI);
        // ctx.fill();

        draw();
        
    }
})