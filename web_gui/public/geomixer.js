class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

class Line {
    constructor(point1, point2) {
        this.p1 = point1;
        this.p2 = point2;
    }
}

class Mouse {
    constructor() {
        this.xpos = 0;
        this.ypos = 0;
        this.insideShape = false;
    }

    get coordinates() {
        return {x: this.xpos, y: this.ypos};
    }

    updatePos(event, yOffset) {
        this.xpos = event.pageX;
        this.ypos = event.pageY - yOffset;
    }

    onLine(pointA, pointB) {
        if (this.xpos <= Math.max(pointA.x, pointB.x) 
            && this.xpos <= Math.min(pointA.x, pointB.x)
            && (this.ypos <= Math.max(pointA.y, pointB.y)
            && this.ypos <= Math.min(pointA.y, pointB.y))) {
                return true;
            }
        else {
            return false;
        }
    }

    direction(pointA, pointB, pointC) {
        let val = (pointB.y - pointA.y) * (pointC.x - pointB.x) 
                - (pointB.x - pointA.x) * (pointC.y - pointB.y);
 
        if (val == 0) {
            // Colinear
            return 0;
        }
        else if (val < 0) {
            // Anti-clockwise direction
            return 2;
        }
        else {
            // Clockwise direction
            return 1;
        }
    }

    isIntersect(l1, l2) {
        // Four direction for two lines and points of other line
        let dir1 = this.direction(l1.p1, l1.p2, l2.p1);
        let dir2 = this.direction(l1.p1, l1.p2, l2.p2);
        let dir3 = this.direction(l2.p1, l2.p2, l1.p1);
        let dir4 = this.direction(l2.p1, l2.p2, l1.p2);
    
        // When intersecting
        if (dir1 != dir2 && dir3 != dir4)
            return true;
    
        // When p2 of line2 are on the line1
        if (dir1 == 0 && this.onLine(l1, l2.p1))
            return true;
    
        // When p1 of line2 are on the line1
        if (dir2 == 0 && this.onLine(l1, l2.p2))
            return true;
    
        // When p2 of line1 are on the line2
        if (dir3 == 0 && this.onLine(l2, l1.p1))
            return true;
    
        // When p1 of line1 are on the line2
        if (dir4 == 0 && this.onLine(l2, l1.p2))
            return true;
    
        return false;
    }

    isInsideShape(shape) {
        if (shape.points.length < 3) {
            return false;
        }

        let mousePoint = new Point(this.xpos, this.ypos)
        let infinityPoint = new Point(99999999, mousePoint.y);
        let exline = new Line(mousePoint, infinityPoint);

        let count = 0;

        for (let j = 0; j < shape.points.length; j++) {
            let side;
            if (j == (shape.points.length - 1)) {
                side = new Line(shape.points[j], shape.points[0]);
            }
            else {
                side = new Line(shape.points[j], shape.points[j + 1]);
            }
            if (this.isIntersect(side, exline)) {
                count ++;
            }
        }

        if ((count % 2) == 1) {
            return true;
        }
        else {
            return false;
        }
    }
}

class Shape {
    constructor(canvas) {
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');

        this.points = [];
        this.xMin = 0;
        this.xMax = 0;
        this.yMin = 0;
        this.yMax = 0;
    }

    createPoint(x, y, div, parentDiv, name) {
        let point = {
            x: x, 
            y: y, 
            div: div
        };

        this.stylePoint(point, div, parentDiv, name);
        this.points.push(point);
    }

    deletePoint(point, pointIndex, parentDiv) {
        if (point.div.id == "deleteMe") {
            parentDiv.removeChild(point.div);
            this.points.splice(pointIndex, 1);
            this.update();
            return true;
        }
        else {
            return false;
        }
    }

    stylePoint(point, div, parentDiv, name) {
        div.className = 'effect';
        div.style.left = String(point.x - 25) + 'px';
        div.style.top = String(point.y - 25) + 'px';
        
        let text = document.createElement('span');
        text.innerHTML = name;
        div.appendChild(text);

        div.addEventListener("click", (event) => {
            if (div.id == "deleteMe") {
                div.id = "";
                div.style.backgroundColor = '#bbb';
            }
            else {
                div.style.backgroundColor = 'red';
                div.id = "deleteMe";
            }
        })

        parentDiv.appendChild(div);
    }

    draw() {
        // clear canvas
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);

        // begin draw for shape between clicked points
        this.ctx.beginPath();
        if (this.points.length > 1) {
            this.ctx.moveTo(this.points[0].x, this.points[0].y);

            // for each click point make a shape
            for (let i = 1; i < this.points.length; i++) {
                this.ctx.lineTo(this.points[i].x, this.points[i].y);
                this.ctx.fill()
            }
        }
    }

    updateMaxMin() {
        this.xMin = this.points[0].x;
        this.xMax = this.points[0].x;
        this.yMin = this.points[0].y;
        this.yMax = this.points[0].y;
        for (let j = 0; j < this.points.length; j++) {
            if (this.points[j].x < this.xMin) {
                this.xMin = this.points[j].x;
            }
            else if (this.points[j].x > this.xMax) {
                this.xMax = this.points[j].x;
            }
    
            if (this.points[j].y < this.yMin) {
                this.yMin = this.points[j].y;
            }
            else if (this.points[j].y > this.yMax) {
                this.yMax = this.points[j].y;
            }
        }
    }

    update() {
        this.draw();
        this.updateMaxMin();
    }
}

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