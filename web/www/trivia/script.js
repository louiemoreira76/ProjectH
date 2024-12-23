// Lógica para a pergunta de múltipla escolha
document.querySelectorAll(".option").forEach(button => {
    button.addEventListener("click", function () {
        const isCorrect = button.getAttribute("data-correct") === "true";
        const feedback = document.getElementById("feedback-multiple-choice");
        
        if (isCorrect) {
            button.style.backgroundColor = "green";
            feedback.textContent = "Correct!";
            feedback.className = "feedback correct";
        } else {
            button.style.backgroundColor = "red";
            feedback.textContent = "Incorrect";
            feedback.className = "feedback incorrect";
        }
    });
});

// Lógica para a pergunta de resposta livre
document.getElementById("submit-response").addEventListener("click", function () {
    const input = document.getElementById("free-response-input");
    const feedback = document.getElementById("feedback-free-response");
    const userAnswer = input.value.trim().toLowerCase();
    const correctAnswer = "paris";

    if (userAnswer === correctAnswer) {
        input.style.backgroundColor = "green";
        feedback.textContent = "Correct!";
        feedback.className = "feedback correct";
    } else {
        input.style.backgroundColor = "red";
        feedback.textContent = "Incorrect!";
        feedback.className = "feedback incorrect";
    }
});
