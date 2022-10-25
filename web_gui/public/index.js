// Get the web page body
const gui = document.body;

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

gui.addEventListener("mousemove", mouseCoords, false);