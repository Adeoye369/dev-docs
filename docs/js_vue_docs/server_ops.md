# Server Operations

## Recommended Status Codes

**401 Unauthorized:** This is the primary code for authentication failure. It indicates that the request lacks valid credentials for the target resource.

**403 Forbidden:** Used when the user is successfully authenticated but lacks the necessary permissions to access a specific resource (e.g., a standard user trying to access an admin panel). It is also sometimes used for accounts that are suspended or blocked.

**400 Bad Request:** Appropriate for malformed login requests, such as missing required fields (e.g., an empty password field) or invalid syntax in the request body.

**422 Unprocessable Entity:** Frequently used in modern APIs to indicate semantic errors, such as a password that does not meet security requirements or an email format that is valid but not found in the system.

**429 Too Many Requests:** Used for rate-limiting after multiple failed login attempts to prevent brute-force attacks.

## Runing Json server

1. Install `json-server` using `npm i json-server`
2. Rename your `jobs.json` to be in this format

    ```json
          {
            "jobs":[
              {...job1 details},
              {...job2 details},
              ...
            ]
          }
    ```

3. In your *package.json* file, at the script section add `server`

    ```json hl_lines="11"
            {
              "name": "vue001_introduction",
              "version": "0.0.0",
              "private": true,
              "type": "module",
              "scripts": {
                "dev": "vite",
                "build": "vite build",
                "preview": "vite preview",
                "server1": "json-server --watch src/jobs.json --port 1234"
              },
                ...
            }
    ```

4. Create new terminal in vscode `ALT + CTRL + (~)`
then run `npm run server1` server1 being the name you decide.

5. Install Axios `npm i axios`  that will be used to run CRUD operation
6. In the *JobListings.vue* do the following

    ```html title="JobListings.vue" hl_lines="2 3 7-9 18-26 36"
    <script setup>
    import {ref, reactive, onMounted} from 'vue' // add onMounted
    import axios from 'axios'                   // Add axios
    import JobListing from '@/components/JobListing.vue'

    // Change ref to reactive
    const state = reactive({ 
        jobs: [],
        isLoading: true
    })

    defineProps({
        limit: Number,
        showAllJobs: {type: Boolean, default: false}
    })

    // Loading jobs from Json server
    onMounted(async () =>{
        try {
            const response = await axios.get("http://localhost:1234/jobs")
            state.jobs = response.data
        } catch (error) {
            console.error("Error fetching jobs : ",  error)
        } finally{
            state.isLoading = false;
        }
    })

    </script>

    <template>
        ...
                <div class="grid grid-cols-1 md:grid-cols-3 gap-6">
                    <!-- Display on limit amount -->
                    <JobListing 
                    v-for="job in state.jobs.slice(0, limit || state.jobs.length)" 
                    :job-data="job" />
                </div>
            </div>
        </section>

       ...
    </template>
    ```

## Replacing LocalHost with '/api'

```js title="vite.config.js" hl_lines="6-14"
export default defineConfig({
  plugins: [
    vue(),
    ...
  ],
  server:{
    proxy: {
      '/api' : {
        target:'http://localhost:1234',
        changeOrigin: true,
        rewrite: (path)=>path.replace(/^\/api/, '')
      }
    }
  },
  resolve: {
    ...
  },
})

```

## Sending Email Via Nodemail and SendGrid

install the following dependencies

```bash
npm i nodemailer  dotenv
```

### Setup mailing utility function

```js title="mailer.js"
import nodemailer from "nodemailer"
import "dotenv/config"

const transport = nodemailer.createTransport({
        host: "smtp.sendgrid.net",
        port: 587,  // Recommended for STARTTLS
        secure: false, // must be false
        auth:{
            user: "apikey",  // This is exactly "apikey" for everyone
            pass: process.env.SENDGRID_API_KEY // Your secret key (SG.xxx)
        }
   }
)

/**
 * Sends an email using the SMTP transporter.
 * @param {string} to - Recipient email
 * @param {string} subject - Email subject line
 * @param {string} html - HTML body content
 */
const sendMail = (mailInfo) =>{

    transport.sendMail({
        from: process.env.SENDER_EMAIL,
        ...mailInfo
    })
}

/** 
 * Alternatively, you can do
const sendMail = (to, subject, html) =>{

    transport.sendMail({
        from: process.env.SENDER_EMAIL,
        to, 
        subject,
        html
    })
}
*/
export default sendMail
```

Then in your route directory you can call `sendMail()`

```js
export async function postSignup(req, res){

    try {
    
        const{email, password, confirmPassword } = req.body
     
       . . .

                // sendMail to user
                await sendMail({
                    to : email,
                    subject: "Welcome to Node 05 community",
                    html:`<strong>Welcome, ${email}</strong>, to the Node 05 Test Community.\n
                    We will like you to verify that this is actually your email`
                })
                //OR await sendMail(to=email, subject="...", html="<>SomeHtml<>")

                res.json({userDetails: user, message: "NEW USER CREATED"})
            }
        
    } catch (error) {
      res.status(500).json({
        message: "Failed to Signup : "+ error.response.body || error
    })  
    }

}
```

## Basics of Express Validator

```js
import * as express from 'express';
import { query, matchedData, validationResult } from 'express-validator';
const app = express();

app.use(express.json());

app.get('/hello', body('person').notEmpty().escape(), 
  (req, res) => {
    const result = validationResult(req);
    if (result.isEmpty()) {
      const data = matchedData(req);   
      return res.send(`Hello, ${data.person}!`);
    }

    res.send({ errors: result.array() });
  });

app.listen(3000);
```

## Show Message Count Down

```js
const message = ref('')
const isMsgVisible = ref(false)

const showMessage = (timeInSec) =>{
    isMsgVisible.value = true
    message.value = route.query?.signupMsg || ""

    if(isMsgVisible){
        setTimeout(()=>{
                isMsgVisible.value = false
        }, timeInSec*1000)
    }

}

. . .

// it can also be @click button
onMounted(()=>{
    showMessage(5)
})

. . .
// call use the
        <transition name='fade'>
              <div v-if="message && isMsgVisible" style="color: #ff00aa; background-color: #220022; padding: 10px;">
                  <p>{{ message }}</p>
              </div>
        </transition>

// css
<style>
  .fade-enter-active, .fade-leave-active { 
    transition: opacity 0.5s; 
}
.fade-enter-from, .fade-leave-to { 
    opacity: 0; 
}
</style>
```
