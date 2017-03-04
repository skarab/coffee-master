function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6294\" class=\"headerLeftMenuInActive\"><a id=\"aID6294\" href=\"#\" OnMouseOver=\"link('_dir','core0',this)\" class=\"leftMenuLinkHeadInActive\">core</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6295\" class=\"leftMenuInActive\"><a id=\"aID6295\" href=\"#\" OnMouseOver=\"link('_dir','error/error0',this)\" class=\"leftMenuLinkInActive\">error</a></div>\n");
document.write("<div id=\"divID6296\" class=\"leftMenuInActive\"><a id=\"aID6296\" href=\"#\" OnMouseOver=\"link('_dir','log/log0',this)\" class=\"leftMenuLinkInActive\">log</a></div>\n");
document.write("<div id=\"divID6297\" class=\"leftMenuInActive\"><a id=\"aID6297\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6298\" class=\"leftMenuInActive\"><a id=\"aID6298\" href=\"#\" OnMouseOver=\"link('_dir','memory/memory0',this)\" class=\"leftMenuLinkInActive\">memory</a></div>\n");
document.write("<div id=\"divID6299\" class=\"leftMenuInActive\"><a id=\"aID6299\" href=\"#\" OnMouseOver=\"link('_dir','platform/platform0',this)\" class=\"leftMenuLinkInActive\">platform</a></div>\n");
document.write("<div id=\"divID6300\" class=\"leftMenuInActive\"><a id=\"aID6300\" href=\"#\" OnMouseOver=\"link('_dir','processor/processor0',this)\" class=\"leftMenuLinkInActive\">processor</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
