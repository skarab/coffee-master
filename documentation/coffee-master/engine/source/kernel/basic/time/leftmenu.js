function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6293\" class=\"headerLeftMenuInActive\"><a id=\"aID6293\" href=\"#\" OnMouseOver=\"link('_dir','time0',this)\" class=\"leftMenuLinkHeadInActive\">time</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID757\" class=\"leftMenuInActive\"><a id=\"aID757\" href=\"#\" OnMouseOver=\"link('_class','Clock39014',this)\" class=\"leftMenuLinkInActive\">Clock</a></div>\n");
document.write("<div id=\"divID758\" class=\"leftMenuInActive\"><a id=\"aID758\" href=\"#\" OnMouseOver=\"link('_class','Date39014',this)\" class=\"leftMenuLinkInActive\">Date</a></div>\n");
document.write("<div id=\"divID759\" class=\"leftMenuInActive\"><a id=\"aID759\" href=\"#\" OnMouseOver=\"link('_class','Time39014',this)\" class=\"leftMenuLinkInActive\">Time</a></div>\n");
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
