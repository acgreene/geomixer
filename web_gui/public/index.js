///// STATIC DOM OBJECTS /////
const gui = document.body;
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
const overlay = document.getElementById('overlay');
const title = document.getElementById('title');
const toolbar = document.getElementById('toolbar');
const deleteEffectsButton = document.getElementById('delete-fx-button');
const fxSelector = document.getElementById('fxSelector');

///// GEOMIXER OBJECTS /////
let mouse = new Mouse();
let shape = new Shape(canvas);

///// INTERACTIONS WITH SERVER /////
function postMouseCoords(event) {
    let yOffset = toolbar.offsetHeight;
    mouse.updatePos(event, yOffset);

    if (mouse.isInsideShape(shape) == false) {
        ctx.fillStyle = 'black';
        ctx.fill();
        return;
    }
    else {
        ctx.fillStyle = 'red';
        ctx.fill();
        // TO DO: instead of sending mouse coords, send mix amounts
        doFetch('/mouse', 'POST', mouse.coordinates, 'Unable to send mouse coords')
    }
}
canvas.addEventListener("mousemove", postMouseCoords, false);

////// CANVAS FUNCTIONALITIY /////
function sizeCanvas() {
    canvas.width = window.innerWidth;
    canvas.height = gui.offsetHeight - toolbar.offsetHeight;
}
sizeCanvas();

// create point on canvas
canvas.addEventListener("click", (event) => {
    // obtain click coordinates
    let xClick = event.clientX;
    let yClick = event.clientY - toolbar.offsetHeight;

    // create effect div
    let effect = document.createElement('div');
    let fxName = fxSelector.options[fxSelector.selectedIndex].text; 

    // create point using coordinates and div
    shape.createPoint(xClick, yClick, effect, overlay, fxName);
    
    // update the shape properties
    shape.update();
})

// delete point on canvas from delete fx button
deleteEffectsButton.addEventListener("click", (event) => {
    for (let j = 0; j < shape.points.length; j++) {
        if (shape.deletePoint(shape.points[j], j, overlay)) {
            j--;
        }
    }
    shape.update();
})