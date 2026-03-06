# Learning Vue using Typescript

## Example marking Input Auto Focus

### Js Declaration

```js

import type { Directive } from 'vue'

// v-focus custom directive
const vFocus: Directive<HTMLInputElement> = {
  mounted: (el) => el.focus(),
}
```

### Usage

```html hl_lines='5'
<input
              type="text"
              class="edit-input"
              . . .
              v-focus
            />
```