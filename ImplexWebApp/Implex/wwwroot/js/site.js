
function generateMatrixInput(id, height, width) {
    const matrixInput = document.getElementById(id);
    matrixInput.innerHTML = "&nbsp";
    let index;
    for (let i = 0; i < height; i ++) {
        const row = document.createElement("div");
        row.className = "form-row";
        for (let j = 0; j < width; j ++) {
            if (height === 1) index = j;
            else index = i;
            const col = document.createElement("div");
            col.className = "col my-1";
            const inputElement = document.createElement("input");
            inputElement.type = "text";
            inputElement.required = true;
            inputElement.className = "form-control";
            inputElement.name = id + "[" + index + "]";
            col.appendChild(inputElement);
            row.appendChild(col);
        }
        matrixInput.appendChild(row);
    }
}

function generateSystemInput(matrixInputId, vectorInputId, size) {
    generateMatrixInput(vectorInputId, size, 1);
    generateMatrixInput(matrixInputId, size, size);
}

function generateJacobiSystemInput(matrixInputId, vectorInputId, initialValuesId, sizeId) {
    const sizeInput = document.getElementById(sizeId);

    let size = sizeInput.value;
    generateSystemInput(matrixInputId, vectorInputId, size);
    generateMatrixInput(initialValuesId, 1, size);
}

function generateMatrixMultiplicationInput(matrixAInputId, matrixBInputId, nSizeId, mSizeId, pSizeId) {
    const nSizeInput = document.getElementById(nSizeId);
    const mSizeInput = document.getElementById(mSizeId);
    const pSizeInput = document.getElementById(pSizeId);

    let nSize = nSizeInput.value;
    let mSize = mSizeInput.value;
    let pSize = pSizeInput.value;

    generateMatrixInput(matrixAInputId, nSize, mSize);
    generateMatrixInput(matrixBInputId, mSize, pSize);
}

let animateButton = function (e) {

    e.preventDefault;
    //reset animation
    e.target.classList.remove('animate');

    e.target.classList.add('animate');

    e.target.classList.add('animate');
    setTimeout(function () {
        e.target.classList.remove('animate');
    }, 6000);
};

const classname = document.getElementsByClassName("button");

for (let i = 0; i < classname.length; i++) {
    classname[i].addEventListener('click', animateButton, false);
} 