
const sizeInput = document.getElementById("size");
const widthInput = document.getElementById("width");
const heightInput = document.getElementById("height");


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

function generateJacobiSystemInput(matrixInputId, vectorInputId, initialValuesId) {
    let size = sizeInput.value;
    generateSystemInput(matrixInputId, vectorInputId, size);
    generateMatrixInput(initialValuesId, 1, size);
}
