# Databae Migration with Sequelize

## Migration Functions

```js

import  sequelize  from "../utils/database.js";
import { Sequelize } from "sequelize";

export async function updateProductsTable() {
    const queryInterface = sequelize.getQueryInterface()

    try {
        // Fetch current table structure to prevent "column already exists" errors
        const tableInfo = queryInterface.describeTable('Products')

        // add mediapreview if missing
        if(!tableInfo.mediapreview){
           await queryInterface.addColumn('Products', 'mediapreview', {
                 type: Sequelize.STRING,
                 defaultValue: ''
            })

            console.log('Successfully added "mediapreview" column.');
        }


    } catch (error) {
        console.error('Error migrating Products table:', error);
    }
}

export async function renameProductsTableField(){

    const queryInterface = sequelize.getQueryInterface()

    try {
        const tableInfo = queryInterface.describeTable('Products')

         // Normalize keys to lowercase to fix any case-sensitivity bugs
        const columns = Object.keys(tableInfo).map(key => 
          { 
            console.log("Key:", key)
            return key.toLowerCase()
        }
        )
        
        const hasOldField = columns.includes('imagepath');
        const hasNewField = columns.includes('mediapath');
        console.log("TableInfo: ", columns)
    
        if (hasOldField && !hasNewField) {
            // Standard Sequelize rename
            await queryInterface.renameColumn('Products', 'imagePath', 'mediaPath');
            console.log('Successfully renamed field from "imagePath" to "mediaPath".');
          } else if (hasOldField && hasNewField) {
            // If sync() accidentally created an empty 'mediaPath' AND 'imagePath' still exists with your data:
            console.log('Both fields detected. Merging and dropping old column safely...');
            
            // Copy any remaining data from old to new just in case
            await sequelize.query('UPDATE Products SET mediaPath = imagePath WHERE mediaPath IS NULL OR mediaPath = ""');
            // Drop the old column
            await queryInterface.removeColumn('Products', 'imagePath');
            console.log('Merged data and removed old "imagePath" column.');
          } else {
            console.log('Rename skipped: "imagePath" column no longer exists.');
          }
        } catch (error) {
          console.error('Error renaming product field, executing raw MySQL fallback...', error);
          
          // Raw SQL Fallback if Sequelize queryInterface gets locked up by constraints
          try {
            await sequelize.query('ALTER TABLE Products CHANGE COLUMN imagePath mediaPath VARCHAR(255);');
            console.log('Raw SQL Fallback: Successfully renamed imagePath to mediaPath.');
          } catch (rawError) {
            console.log('Column may already be renamed:', rawError.message);
        }
    }
}
```

## Call Functions After sequelize.sync()

```js
. . .
        await sequelize.sync();
        await renameProductsTableField()
        await updateProductsTable()
. . .
       
```
