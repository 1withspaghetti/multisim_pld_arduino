<script lang="ts">
    import processVHDL from "./lib/processVHDL";


    let files: FileList | null = $state(null);
    let bytecode: ArrayBuffer | null = $state(null);

    function onsubmit(e: SubmitEvent) {
        bytecode = null;
        e.preventDefault();
        
        // Get content as string
        if (!files) return;
        const reader = new FileReader();
        reader.onload = (event) => {
            const content = event.target?.result;
            process(content as string);
        };
        
        reader.readAsText(files[0]);
    }

    function process(content: string) {
        try {
            bytecode = processVHDL(content);
        } catch (error) {
            console.error('Error processing file:', error);
        }
    }


    const hex = $derived.by(() => {
        if (!bytecode) return '';
        const hexArray = Array.from(new Uint8Array(bytecode)).map(b => b.toString(16).padStart(2, '0'))
        return hexArray.join('');
    })
    const cpp_code = $derived.by(() => {
        if (!bytecode) return '';
        const hexArray = Array.from(new Uint8Array(bytecode)).map(b => "0x"+b.toString(16).padStart(2, '0'))
        return `{ ${hexArray.join(', ')} }`;
    })
    
    function copyToClipboard(str: string) {
        navigator.clipboard.writeText(str).then(() => {
            alert('Copied to clipboard!');
        }).catch(err => {
            console.error('Failed to copy: ', err);
        });
    }
    
</script>

<main class="p-8 flex flex-col items-center">
    <form onsubmit={onsubmit} class="container mx-auto flex flex-col items-center">
        <input bind:files={files} type="file" accept=".vhd" class="w-full max-w-xs" />
        <div class="flex justify-center gap-4 mt-4">
            <button type="submit" class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded">
                Upload
            </button>
        </div>
    </form>
    {#if bytecode}
        <div class="mt-4 bg-gray-100 p-4 rounded shadow-md">
            <h2 class="text-xl font-bold mb-2">Bytecode</h2>
            <div class="flex gap-4 mb-4">
                <button class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded"
                    onclick={() => {
                        copyToClipboard(hex);
                    }}
                >
                    Copy as hex
                </button>
                <button class="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded"
                    onclick={() => {
                        copyToClipboard(cpp_code);
                    }}
                >
                    Copy as C++
                </button>
            </div>
            <code class="max-w-lg text-sm">{new Uint8Array(bytecode).join(', ')}</code>
        </div>
    {/if}
</main>
