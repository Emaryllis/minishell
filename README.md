<h1><u>Minishell</u></h1>

<h2>Requirements:</h2>
<ol>
    <li>Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).</li>
    <li>Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.</li>
    <li>Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).</li>
    <li>Handle environment variables ($ followed by a sequence of characters) which should expand to their values.</li>
    <li>Handle $? which should expand to the exit status of the most recently executed foreground pipeline.</li>
    <li>Handle ctrl-C, ctrl-D <b>[100% Done]</b> and ctrl-\ which should behave like in bash.</li>
    <li>In interactive mode:
        <ul>
            <li>ctrl-C displays a new prompt on a new line.</li>
            <li>ctrl-D exits the shell. <b>[100% Done]</b></li>
            <li>ctrl-\ does nothing.</li>
        </ul>
    </li>
    <li>Must implement the following built-in commands:
        <ul>
            <li>echo with option -n <b>[100% Done]</b></li>
            <li>cd with only a relative or absolute path</li>
            <li>pwd with no options <b>[100% Done]</b></li>
            <li>export with no options</li>
            <li>unset with no options</li>
            <li>env with no options or arguments <b>[100% Done]</b></li>
            <li>exit with no options <b>[100% Done]</b></li>
        </ul>
    </li>
</ol>