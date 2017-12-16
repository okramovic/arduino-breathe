const synth = window.speechSynthesis

let voices = null;

synth.onvoiceschanged = function(){
    voices = synth.getVoices() 
    console.log(voices)
}

// english options:
// 65 - google US english
// 66 - seems best - google UK english female

say = null;
utter = new SpeechSynthesisUtterance(say)
utter.voice = voices[66]

synth.speak(utter)