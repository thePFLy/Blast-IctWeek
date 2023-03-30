import requests, json
from flask import Flask, jsonify

app = Flask(__name__) 
api_key = 'NNSXS.SGEPGD5KHWRIQPRWMIQY6VJFQDDS2ZIIBLURM3Q.JH3KTSCTCZ4CEDGTW7RCHV2SQHD57PLFFJX6LEO2XFFF3Y6FGN5A' 
url = 'https://eu1.cloud.thethings.network/api/v3/as/applications/ict-team4/packages/storage/' 
 
@app.route('/') 
def hello():
    return 'main page' 
 
@app.route('/data') 
def data(): 
    headers_auth = {'Authorization': 'Bearer ' + api_key} 
 
    response = requests.get(url, headers=headers_auth)
    data_list = []
    for j in response.text.split('\n'):
        if j == "":
            print("")
        else:
            d=json.loads(j)
            data_list.append(d)
            data_list.append(d['result']['uplink_message']['frm_payload'])
    return jsonify(data_list)
 
if __name__ == '__main__':
    app.run(debug=True)
