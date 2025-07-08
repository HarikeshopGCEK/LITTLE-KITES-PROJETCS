from flask import Flask, send_from_directory

app = Flask(__name__)
led_State = 0  # <-- Add this line
@app.route('/')
def home():
    return send_from_directory('', 'index.html')
@app.route('/led')
def led_control():
    return str(led_State)
@app.route('/led/on')
def led_on():
    global led_State
    led_State = 1
    return "1"
@app.route('/led/off')
def led_off():
    global led_State
    led_State = 0
    return "0"
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)