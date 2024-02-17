let btn = document.getElementById("btn");
btn.addEventListener("click", function () {
  let input = document.getElementById("todoinput");
  let ul = document.getElementById("unorder");
  let li = document.createElement("li");
  let inputTodo = document.createElement("input");
  inputTodo.setAttribute("type", "text");
  inputTodo.setAttribute("value", input.value);
  li.appendChild(inputTodo);
  ul.appendChild(li);

  console.log(inputTodo);
});