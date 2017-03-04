function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6328\" class=\"headerLeftMenuInActive\"><a id=\"aID6328\" href=\"#\" OnMouseOver=\"link('_dir','shell0',this)\" class=\"leftMenuLinkHeadInActive\">shell</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6325\" class=\"leftMenuInActive\"><a id=\"aID6325\" href=\"#\" OnMouseOver=\"link('_dir','event/event0',this)\" class=\"leftMenuLinkInActive\">event</a></div>\n");
document.write("<div id=\"divID6326\" class=\"leftMenuInActive\"><a id=\"aID6326\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6327\" class=\"leftMenuInActive\"><a id=\"aID6327\" href=\"#\" OnMouseOver=\"link('_dir','module/module0',this)\" class=\"leftMenuLinkInActive\">module</a></div>\n");
document.write("<div id=\"divID6329\" class=\"leftMenuInActive\"><a id=\"aID6329\" href=\"#\" OnMouseOver=\"link('_dir','state/state0',this)\" class=\"leftMenuLinkInActive\">state</a></div>\n");
document.write("<div id=\"divID6330\" class=\"leftMenuInActive\"><a id=\"aID6330\" href=\"#\" OnMouseOver=\"link('_dir','thread/thread0',this)\" class=\"leftMenuLinkInActive\">thread</a></div>\n");
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
