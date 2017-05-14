﻿using System.Collections.Generic;
using System.Windows.Input;

namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// The service provides an access to actions. 
    /// </summary>
    public interface IAimpServiceActionManager
    {
        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="action">The action.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult GetById(string id, out IAimpAction action);

        /// <summary>
        /// Makes the hotkey.
        /// </summary>
        /// <param name="modifiers">The key modifiers <see cref="ModifierKeys"/>.</param>
        /// <param name="key">The key.</param>
        /// <returns></returns>
        int MakeHotkey(ModifierKeys modifiers, uint key);

        /// <summary>
        /// Registers the specified action.
        /// </summary>
        /// <param name="action">The action <see cref="IAimpAction"/>.</param>
        AimpActionResult Register(IAimpAction action);

        /// <summary>
        /// Registers the specified actions.
        /// </summary>
        /// <param name="actions">The collection of <see cref="IAimpAction"/>.</param>
        AimpActionResult Register(ICollection<IAimpAction> actions);
    }
}