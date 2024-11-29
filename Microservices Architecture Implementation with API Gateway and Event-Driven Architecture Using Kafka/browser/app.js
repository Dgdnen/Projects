const express = require('express');

const port = 3003;
const api_gateway_url = "http://localhost:3000/"

// Create an express app
const app = express();

// Add middleware
app.use(express.urlencoded({ extended: true }));
app.use(express.json());
app.use(express.static('images'));

// Create a route for GET request
app.get('/', (req, res) => {
    console.log("GET called");
    res.sendFile(__dirname + '/page.html');
});

app.post("/", (req, res) => {
    console.log(req.body);

    const req_type = req.body.type_name; // client or company
    const req_val = req.body.val_name; // name client or company

//CASE: CLIENT

    const fetchClient = async (cl_name) => {
        const response = await fetch(api_gateway_url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ type_name: "cl", val_name: cl_name })
        });

        const data = await response.json();
        console.log(`Received ${data} from api_gateway`);

        if (data.ok) {
            var result = "Informatia cautata a returnat urmatorul rezultat.";
            result += "<table><tr><td>Avere detinuta</td><td>" + data.avere + "</td></tr>";
            result += "<tr><td>Functie in companie</td><td>" + data.functie + "</td></tr></table>";
            return result;
        } else {
            return "Nu s-a gasit niciun rezultat in baza de date.";
        }
    };


//CASE: COMPANY

    const fetchCompany = async (co_name) => {
        const response = await fetch(api_gateway_url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ type_name: "co", val_name: co_name })
        });

        const data = await response.json();
        console.log(`Received ${data} from api_gateway`);

        if (data.ok) {
            var result = "Informatia cautata a returnat urmatorul rezultat.";
            result += "<table><tr><td>Valoare</td><td>" + data.valoare + "</td></tr>";
            result += "<tr><td>Numar</td><td>" + data.nr + "</td></tr></table>";
            return result;
        } else {
            return "Nu s-a gasit niciun rezultat in baza de date.";
        }
    };

    if (req_type === "cl") {
        fetchClient(req_val).then(cl_res => {
            res.json({ result: cl_res });
        });
    } else if (req_type === "co") {
        fetchCompany(req_val).then(co_res => {
            res.json({ result: co_res });
        });
    }
});

app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
