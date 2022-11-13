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
function postMix(event) {
    let yOffset = toolbar.offsetHeight;
    mouse.updatePos(event, yOffset);

    if (mouse.isInsideShape(shape) == false) {
        ctx.fillStyle = 'rgb(26, 108, 118)';
        ctx.fill();
        return;
    }
    else {
        ctx.fillStyle = 'rgb(191, 237, 244)';
        ctx.fill();

        // compute distance between mouse and each point
        let effectMixes = []; 
        let totalDist = 0;
        for (let j = 0; j < shape.points.length; j++) {
            // distance formula
            let xDiff = (mouse.xpos - shape.points[j].x) ** 2;
            let yDiff = (mouse.ypos - shape.points[j].y) ** 2;
            let dist = Math.sqrt(xDiff + yDiff);
            
            totalDist += dist;

            let fxName = shape.points[j].div.children[0].innerHTML; 

            let effectMix = {
                name: fxName,
                mix: dist
            }
            effectMixes.push(effectMix);
        }

        // create percentage blends for each distance
        for (let j = 0; j < effectMixes.length; j++) {
            effectMixes[j].mix = (effectMixes[j].mix / totalDist);
        }

        // post blends to server
        doFetch('/mouse', 'POST', effectMixes, 'Unable to send mouse coords')
    }
}
canvas.addEventListener("mousemove", postMix, false);

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